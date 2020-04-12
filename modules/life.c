#include "life.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
int compare_structs(Pointer a,Pointer b)  { //δημιουργια μιας σειρας διαταξης ομοιας της προσπελασης ενος δισδιαστατου πινακα 
    if (((LifeCell*) a)->x==((LifeCell*) b)->x)  {
        return ((LifeCell*) a)->y-((LifeCell*) b)->y;
    }
    else  {
        return ((LifeCell*) a)->x-((LifeCell*) b)->x;
    }
}
int compare_states(Pointer State1,Pointer State2)  {  //εφοσον δε με ενδιαφερει η διαταξη των καταστασεων , αρκει να ξερω ποτε ειναι ισες και ποτε οχι 
    State1=(LifeState*) State1; 
    State2=(LifeState*) State2;
    if (set_size(State1)!=set_size(State2))  { // αν δυο καταστασεις δεν εχουν ιδιο αριθμο ζωντανων κελιων δεν εχει νοημα να τις συγκρινω 
        return 1;
    }
    else  {
        SetNode node1;
        LifeCell Entity;
        node1=set_first(State1);
        while (node1!=SET_EOF)  {
            Entity=*(LifeCell*)set_node_value(State1,node1);
            if (set_find_node(State2,&Entity)==SET_EOF)  { //αν ενα ζωντανο κελι της μιας καταστασης δεν υπαρχει στην αλλη κατασταση τοτε εινια διαφορετικες
                return 1;
            }
            node1=set_next(State1,node1); 
        }
    }
    return 0; // αν δε βρεθει καμια διαφορα τοτε εινια ιδιες
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
    x=0; //θεωρω οτι αρχιζουμε απο το (0,0)
    y=0;
    temp=-1; // μετρητης ο οποιος οταν βρεθει καποιο συμβολο πχ o,b,$ το εφαρμοζει temps φορες
    while((ch=fgetc(fp))!='!')  {
        if (ch=='b')  { //αν βρεθει νεκρο τοτε το σκιπαρουμε
            x++;
            if (temp!=-1)  {
                while (temp-->1)  {
                    x++;
                }
                temp=-1;
            }
        }
        else if (ch=='o')  {
            Cell.x=x;
            Cell.y=y;    //αν βρεθει ζωντανο το καταχωρουμε στο σετ με τις συντεταγμενες που θα εχει
            Entity=create_struct(Cell.x,Cell.y);
            set_insert(Universe,Entity);
            x++;
            if (temp!=-1)  {
                while (temp-->1)  {
                    Cell.x=x;
                    Cell.y=y;
                    Entity=create_struct(Cell.x,Cell.y);
                    set_insert(Universe,Entity);
                    x++;
                }
            }
            temp=-1;
        }
        else if (ch=='$')  {
            y--; //σε περιπτωση αλλαγης γραμμης αλλαζουμε τις συντεταγμενες 
            x=0;
            if (temp!=-1)  {
                while (temp-->1)  {
                    y--;
                }
                temp=-1;
            }
        }
        else  { 
            if (temp!=-1)  {  //σε περιπτωση που δωθει οτιδηποτε αλλο απο τα παραπανω , θεωρουμε οτι ειναι αριθμος 
                temp=10*temp+ch-'0'; // επειδη μπορει να εχει πολλα ψηφια συμπεριλαμβανομενου και 0 πχ 100 , με την αρχικοποιηση του temp σε -1  
            }                        // θεωρουμε οτι αν δεν ειναι -1 τοτε ο αριθμος που υπαρχει πρεπει να γινει πολυψηφιος (η απλα να αποκτησει περισσοτερα ψηφια)
            else  {
                temp=ch-'0'; // αλλιως αν εινια -1 τοτε ο αρθμος που δωθηκε καταχωρειται στο temp
            }
        }
    }
    fclose(fp);
    return Universe;
}
void life_save_to_rle(LifeState Universe, char* file)  { // σημειωση αν σε μια γραμμη υπαρχουν μονο νεκρα κελια απο ενα σημειο και μετα
    FILE *fp;         // δεν εχει νοημα να τα γραψουμε στο rle format οποτε το 3o5b$5b3o! γινεται 3o$5b3o!
    SetNode Node;
    LifeCell Cell;
    int left,up,down,right,o_count,b_count;
    fp=fopen(file,"w");
    left=INT_MAX;
    right=INT_MIN;
    down=INT_MAX;
    up=INT_MIN;
    Node=set_first(Universe);
    while (Node!=SET_EOF)  { //με στοχο την αποτυπωση της καταστασης σε rle πρεπει πρωτα να δημιουργησμουμε ενα παραλληλογραμμο με τις μικροτερες δυνατες
        Cell=*(LifeCell*) set_node_value(Universe,Node); //το οποιο να περιεχει ολα τα ζωντανα κελια 
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
        for (int i=up;i>=down;i--)  { //προσπελαση του δισδιαστατου πινακα που νοητα δημιουργησαμε
            b_count=0; // ποσες φορες εχει εμφανιστει νεκρο,ζωντανο κελι αντιστοιχα ετσι ωστε οταν υπαρξει αλλαγη μεταξυ των δυο 
            o_count=0; // μονο τοτε να καταχωρυθει , να μηδενιστει ο μετρητης του και να αρχισει να μετραει ο μετρητης της αλλης καταστασης  
            for (int j=left;j<=right;j++)  {
                LifeCell Cell;
                Cell.y=i;
                Cell.x=j;
                if (life_get_cell(Universe,Cell)==true)  {
                    if (b_count!=0)  {  // οταν διαβαζουμε ενα ζωντανο τοτε καταχωρουμε τα νεκρα 
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
                        if (o_count==1)  { //οταν διαβαζουμε νεα νεκρο τοτε καταχωρουμε τα ζωντανα
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
            if (o_count!=0)  { // σε περιπτωση που γινει αλλαγη γραμμης πριν την καταχωρυση ολων των ζωντανων κανουμε εναν ελεγχο
                if (o_count==1)  {
                    fprintf(fp,"o");
                }
                else  {
                    fprintf(fp,"%do",o_count);
                }
                o_count=0;
            }
            if (i!=down) fprintf(fp,"$"); //σε καθε αλλαφη γραμμης βαζουμε $
        }
    }
    fprintf(fp,"!"); 
    fclose(fp);
}
bool life_get_cell(LifeState Universe,LifeCell Cell)  {
    LifeCell *Entity=create_struct(Cell.x,Cell.y);
    if (set_find_node(Universe,Entity)!=SET_EOF)  { //αν υπαρχει το κελι στο σετ τοτε ειναι ζωντανο , αλλιως ειναι νεκρο
        free(Entity);
        return true;
    }
    else  {
        free(Entity);
        return false;
    }
}
int search_neighbor_cells(LifeState Universe,int x, int y)  {//ελεγχει τους γειτονες ενος κελιου και επιστερφει ποσοι εινια ζωντανα κελια
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
    if (value==true)  {  //δεδομενης της υλοποιησης της ασκησης που εχω εφαρμοσει δεν μου χρησιμευει πουθενα αυτη η συναρτηση, αλλα εδω ειναι η υλοποιηση της συναρτησης
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
    LifeState Alt_Universe=set_create(compare_structs,free); //δημιουργω ενα νεο συνολο και οσα κελια επιζησουν ή ζωντανεψουν τα καταχωρω εκει
    while (node!=SET_EOF)  {
        char temp;
        Cell=*(LifeCell*) set_node_value(Universe,node);
        temp=search_neighbor_cells(Universe,Cell.x,Cell.y);
        if (temp==2 || temp==3)  { 
            LifeCell* Entity=create_struct(Cell.x,Cell.y);
            set_insert(Alt_Universe,Entity);
        }
        LifeCell s1,s2,s3,s4,s5,s6,s7,s8; //μονο τα 8 γειτονικα κελια του καθε ζωντανου πρεπει να κοιτξω αμα θα αλλαξουν κατασταση 
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
        if ((temp==2 && life_get_cell(Universe,s1) )|| temp==3)  { //αυτο μπορει να συμβει μονο εαν ειτε ειναι ζωντανα και εχουν 2 ζωντανους γειτονες
            set_insert(Alt_Universe,create_struct(s1.x,s1.y));  //ειτε εχουν 3 ζωντανους γειτονες
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
    char loop_detected=0;
    *loop=NULL;
    while (steps--!=0)  {
        State=life_evolve(State);
        ListNode lnode;
        lnode=list_first(list);
        if (lnode!=LIST_BOF)  {
            while (true)  {
                if (list_next(list,lnode)!=LIST_EOF)  {
                    if (compare_states(list_node_value(list,lnode),State)==0)  { //τη πρωτη φορα που θα βρεθει loop τοτε στματαμε την εξελιξη 
                        *loop=lnode;  //και βαζουμε στο *loop τον κομβο που συνεβη η επαληψη
                        loop_detected=1;
                        life_destroy(State);
                        break;
                    }
                    if (list_next(list,lnode)!=LIST_EOF)  {
                        lnode=list_next(list,lnode);
                    }
                    else  {
                        break;
                    }
                }
                else  {
                    break;
                }
            }
        }
        if (loop_detected==1)  {
            break;
        }
        else  {
            list_insert_next(list,lnode,State); //αν δεν εχει ξαναεμφανιστει η κατασταση την καταχωρουμε στη λιστα και συνεχιζουμε την εξελιξη
        }
    }
    return list;
}