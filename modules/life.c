#include "life.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
int compare_structs(Pointer a,Pointer b)  {
    if (((LifeCell*) a)->x==((LifeCell*) b)->x)  {
        if (((LifeCell*) a)->y==((LifeCell*) b)->y)  {
            return 0;
        }
        else  {
            return -1;
        }
    }
    else  {
        return 1;
    }
}
LifeCell* create_struct(LifeCell Cell)  {
    LifeCell* Entity;
    Entity=malloc(sizeof(LifeCell));
    Entity->x=Cell.x;
    Entity->y=Cell.y;
    return Entity;
}
LifeState life_create()  {
    LifeState Universe =map_create(compare_structs,free,free);
    return Universe;
}
LifeState life_create_from_rle(char* file)  {
    FILE *fp;
    LifeState Universe=life_create();
    LifeCell Cell;
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
                printf("x %d ",x);
                map_insert(Universe,create_struct(Cell),0);
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
    MapNode Node;
    LifeCell Cell;
    int left,up,down,right,x,y,o_count,b_count;
    //fp=fopen(file,"w");
    left=INT_MAX;
    right=INT_MIN;
    down=INT_MAX;
    up=INT_MIN;
    Node=map_first(Universe);
    while (Node!=MAP_EOF)  {
        Cell=*(LifeCell*) map_node_value(Universe,Node);
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
        Node=map_next(Universe,Node);
    }
    printf("%d %d %d %d",up,down,left,right);
    /*for (int i=up;i>=down;i--)  {
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
        if (i!=down) fprintf(fp,"$");
    }
    fprintf(fp,"!");*/
    fclose(fp);
}
bool life_get_cell(LifeState Universe,LifeCell Cell)  {
    LifeCell *Entity=create_struct(Cell);
    if (map_find_node(Universe,Entity)!=MAP_EOF)  {
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
    s7.y=y;
    s8.x=x-1;
    s8.y=y+1;
    return life_get_cell(Universe,s1)+life_get_cell(Universe,s2)+life_get_cell(Universe,s3)+life_get_cell(Universe,s4)+life_get_cell(Universe,s5)+life_get_cell(Universe,s6)+life_get_cell(Universe,s7)+life_get_cell(Universe,s8);
}
void life_set_cell(LifeState Universe,LifeCell Cell,bool value)  {
    if (value==true)  {
        if (life_get_cell(Universe,Cell)!=true)  {
            LifeCell* Entity=create_struct(Cell);
            map_insert(Universe,Entity,Entity);
        }
    }
    else  {
        if (life_get_cell(Universe,Cell)==true)  {
            map_remove(Universe,&Cell);
        }
    }
}
LifeState life_evolve(LifeState Universe)  {
    MapNode node=map_first(Universe);
    LifeCell Cell,nCell;
    LifeState Alt_Universe=map_create(compare_structs,free,free);
    while (node!=MAP_EOF)  {
        nCell.x=Cell.x;
        nCell.y=Cell.y;
        char temp;
        temp=search_neighbor_cells(Universe,nCell.x,nCell.y);
        if (temp==2 || temp==3)  { 
            LifeCell* Entity=create_struct(nCell);
            map_insert(Alt_Universe,Entity,Entity);
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
        s7.y=Cell.y;
        s8.x=Cell.x-1;
        s8.y=Cell.y+1;
        temp=search_neighbor_cells(Universe,s1.x,s1.y);
        if (temp==2 || temp==3)  {
            map_insert(Alt_Universe,create_struct(s1),create_struct(s1));
        }
        temp=search_neighbor_cells(Universe,s2.x,s2.y);
        if (temp==2 || temp==3)  {
            map_insert(Alt_Universe,create_struct(s2),create_struct(s2));
        }
        temp=search_neighbor_cells(Universe,s3.x,s3.y);
        if (temp==2 || temp==3)  {
            map_insert(Alt_Universe,create_struct(s3),create_struct(s3));
        }
        temp=search_neighbor_cells(Universe,s4.x,s4.y);
        if (temp==2 || temp==3)  {
            map_insert(Alt_Universe,create_struct(s4),create_struct(s4));
        }
        temp=search_neighbor_cells(Universe,s5.x,s5.y);
        if (temp==2 || temp==3)  {
            map_insert(Alt_Universe,create_struct(s5),create_struct(s5));
        }
        temp=search_neighbor_cells(Universe,s6.x,s6.y);
        if (temp==2 || temp==3)  {
            map_insert(Alt_Universe,create_struct(s6),create_struct(s6));
        }
        temp=search_neighbor_cells(Universe,s7.x,s7.y);
        if (temp==2 || temp==3)  {
            map_insert(Alt_Universe,create_struct(s7),create_struct(s7));
        }
        temp=search_neighbor_cells(Universe,s8.x,s8.y);
        if (temp==2 || temp==3)  {
            map_insert(Alt_Universe,create_struct(s8),create_struct(s8));
        }
    }
    life_destroy(Universe);
    return Alt_Universe;
} 
void life_destroy(LifeState Universe)  {
    map_destroy(Universe);
}