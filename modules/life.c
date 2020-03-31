#include "life.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
int compare_structs(Pointer a,Pointer b)  {
    if (((LifeCell*) a)->x==((LifeCell*) b)->x)  {
        return ((LifeCell*) a)->y-((LifeCell*) b)->y;
    }
    else  {
        return ((LifeCell*) a)->x-((LifeCell*) b)->x;
    }
}
int compare_states(Pointer State1,Pointer State2)  {
    State1=(LifeState*) State1;
    State2=(LifeState*) State2;
    if (set_size(State1)!=set_size(State2))  {
        return 1;
    }
    else  {
        SetNode node1;
        LifeCell Entity;
        node1=set_first(State1);
        while (node1!=SET_EOF)  {
            Entity=*(LifeCell*)set_node_value(State1,node1);
            if (set_find_node(State2,&Entity)==SET_EOF)  {
                return 1;
            }
            node1=set_next(State1,node1); 
        }
    }
    return 0;
}
LifeCell* create_struct(int x,int y)  {
    LifeCell* Entity;
    Entity=malloc(sizeof(LifeCell));
    Entity->x=x;
    Entity->y=y;
    return Entity;
}
LifeState life_create()  {
    LifeState Universe =set_create(compare_structs,free);
    return Universe;
}
LifeState life_create_from_rle(char* file)  {
    FILE *fp;
    LifeState Universe=life_create();
    LifeCell Cell;
    LifeCell* Entity;
    char ch;
    int x,y,temp;
    fp=fopen(file,"r");
    x=0;
    y=0;
    temp=1;
    while((ch=fgetc(fp))!='!')  {
        if (ch=='b')  {
            while (temp--!=0)  {
                x++;
            }
            temp=1;
        }
        else if (ch=='o')  {
            while (temp--!=0)  {
                Cell.x=x;
                Cell.y=y;
                Entity=create_struct(Cell.x,Cell.y);
                set_insert(Universe,Entity);
                x++;
            }
            temp=1;
        }
        else if (ch=='$')  {
            y--;
            x=0;
        }
        else  { 
            if (temp!=1)  {
                temp=temp*10;
                temp=temp+ch-'0';
            }
            else  {
                temp=ch-'0';
            }
        }
    }
    fclose(fp);
    return Universe;
}
void life_save_to_rle(LifeState Universe, char* file)  {
    FILE *fp;
    SetNode Node;
    LifeCell Cell;
    int left,up,down,right,x,y,o_count,b_count;
    fp=fopen(file,"w");
    left=INT_MAX;
    right=INT_MIN;
    down=INT_MAX;
    up=INT_MIN;
    Node=set_first(Universe);
    while (Node!=SET_EOF)  {
        Cell=*(LifeCell*) set_node_value(Universe,Node);
        if (Cell.y<down )  {
            down=Cell.y; 
        }
        if (Cell.y>up)  {
            up=Cell.y;
        }
        if (Cell.x>right)  {
            right=Cell.x;
        }
        if (Cell.x<left)  {
            left=Cell.x;
        }
        Node=set_next(Universe,Node);
    }
    if (set_size(Universe)!=0)  {
        for (int i=up;i>=down;i--)  {
            b_count=0;
            o_count=0;
            for (int j=left;j<=right;j++)  {
                LifeCell Cell;
                Cell.y=i;
                Cell.x=j;
                if (life_get_cell(Universe,Cell)==true)  {
                    if (b_count!=0)  {
                        if (b_count==1)  {
                            fprintf(fp,"b");
                        }
                        else  {
                            fprintf(fp,"%db",b_count);
                        }
                        b_count=0;
                    }
                    o_count++;
                }
                else  {
                    if (o_count!=0)  {
                        if (o_count==1)  {
                            fprintf(fp,"o");
                        }
                        else  {
                            fprintf(fp,"%do",o_count);
                        }
                        o_count=0;
                    }
                    b_count++;

                }
            }
            if (o_count!=0)  {
                if (o_count==1)  {
                    fprintf(fp,"o");
                }
                else  {
                    fprintf(fp,"%do",o_count);
                }
                o_count=0;
            }
            if (i!=down) fprintf(fp,"$");
        }
    }
    fprintf(fp,"!");
    fclose(fp);
}
bool life_get_cell(LifeState Universe,LifeCell Cell)  {
    LifeCell *Entity=create_struct(Cell.x,Cell.y);
    if (set_find_node(Universe,Entity)!=SET_EOF)  {
        free(Entity);
        return true;
    }
    else  {
        free(Entity);
        return false;
    }
}
int search_neighbor_cells(LifeState Universe,int x, int y)  {
    LifeCell s1,s2,s3,s4,s5,s6,s7,s8;
    s1.x=x+1;
    s1.y=y;
    s2.x=x+1;
    s2.y=y+1;
    s3.x=x+1;
    s3.y=y-1;
    s4.x=x;
    s4.y=y+1;
    s5.x=x;
    s5.y=y-1;
    s6.x=x-1;
    s6.y=y;
    s7.x=x-1;
    s7.y=y-1;
    s8.x=x-1;
    s8.y=y+1;
    return life_get_cell(Universe,s1)+life_get_cell(Universe,s2)+life_get_cell(Universe,s3)+life_get_cell(Universe,s4)+life_get_cell(Universe,s5)+life_get_cell(Universe,s6)+life_get_cell(Universe,s7)+life_get_cell(Universe,s8);
}
void life_set_cell(LifeState Universe,LifeCell Cell,bool value)  {
    if (value==true)  {
        if (life_get_cell(Universe,Cell)!=true)  {
            LifeCell* Entity=create_struct(Cell.x,Cell.y);
            set_insert(Universe,Entity);
        }
    }
    else  {
        if (life_get_cell(Universe,Cell)==true)  {
            set_remove(Universe,&Cell);
        }
    }
}
LifeState life_evolve(LifeState Universe)  {
    SetNode node=set_first(Universe);
    LifeCell Cell;
    LifeState Alt_Universe=set_create(compare_structs,free);
    while (node!=SET_EOF)  {
        char temp;
        Cell=*(LifeCell*) set_node_value(Universe,node);
        temp=search_neighbor_cells(Universe,Cell.x,Cell.y);
        if (temp==2 || temp==3)  { 
            LifeCell* Entity=create_struct(Cell.x,Cell.y);
            set_insert(Alt_Universe,Entity);
        }
        LifeCell s1,s2,s3,s4,s5,s6,s7,s8;
        s1.x=Cell.x+1;
        s1.y=Cell.y;
        s2.x=Cell.x+1;
        s2.y=Cell.y+1;
        s3.x=Cell.x+1;
        s3.y=Cell.y-1;
        s4.x=Cell.x;
        s4.y=Cell.y+1;
        s5.x=Cell.x;
        s5.y=Cell.y-1;
        s6.x=Cell.x-1;
        s6.y=Cell.y;
        s7.x=Cell.x-1;
        s7.y=Cell.y-1;
        s8.x=Cell.x-1;
        s8.y=Cell.y+1;
        temp=search_neighbor_cells(Universe,s1.x,s1.y);
        if ((temp==2 && life_get_cell(Universe,s1) )|| temp==3)  {
            set_insert(Alt_Universe,create_struct(s1.x,s1.y));
        }
        temp=search_neighbor_cells(Universe,s2.x,s2.y);
        if ((temp==2 && life_get_cell(Universe,s2) ) || temp==3)  {
            set_insert(Alt_Universe,create_struct(s2.x,s2.y));
        }
        temp=search_neighbor_cells(Universe,s3.x,s3.y);
        if ((temp==2 && life_get_cell(Universe,s3) ) || temp==3)  {
            set_insert(Alt_Universe,create_struct(s3.x,s3.y));
        }
        temp=search_neighbor_cells(Universe,s4.x,s4.y);
        if ((temp==2 && life_get_cell(Universe,s4) ) || temp==3)  {
            set_insert(Alt_Universe,create_struct(s4.x,s4.y));
        }
        temp=search_neighbor_cells(Universe,s5.x,s5.y);
        if ((temp==2 && life_get_cell(Universe,s5) ) || temp==3)  {
            set_insert(Alt_Universe,create_struct(s5.x,s5.y));
        }
        temp=search_neighbor_cells(Universe,s6.x,s6.y);
        if ((temp==2 && life_get_cell(Universe,s6) ) || temp==3)  {
            set_insert(Alt_Universe,create_struct(s6.x,s6.y));
        }
        temp=search_neighbor_cells(Universe,s7.x,s7.y);
        if ((temp==2 && life_get_cell(Universe,s7) ) || temp==3)  {
            set_insert(Alt_Universe,create_struct(s7.x,s7.y));
        }
        temp=search_neighbor_cells(Universe,s8.x,s8.y);
        if ((temp==2 && life_get_cell(Universe,s8) ) || temp==3)  {
            set_insert(Alt_Universe,create_struct(s8.x,s8.y));
        }
        node=set_next(Universe,node);
    }
    return Alt_Universe;
} 
void life_destroy(LifeState Universe)  {
    set_destroy(Universe);
}
List life_evolve_many(LifeState State,int steps ,ListNode *loop)   {
    List list=list_create(NULL);
    *loop=NULL;
    while (steps--!=0)  {
        State=life_evolve(State);
        ListNode lnode;
        lnode=list_first(list);
        if (lnode!=LIST_BOF)  {
            while (true)  {
                if (compare_states(list_node_value(list,lnode),State)==0)  {
                    *loop=lnode;
                }
                if (list_next(list,lnode)!=LIST_EOF)  {
                    lnode=list_next(list,lnode);
                }
                else  {
                    break;
                }
            }
        }
        list_insert_next(list,lnode,State);
    }
    return list;
}