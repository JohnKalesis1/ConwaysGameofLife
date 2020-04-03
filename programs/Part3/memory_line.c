#include <stdio.h>
#include "ADTSet.h"
#include <string.h>
#include <stdlib.h>
int compare_strings(Pointer a,Pointer b)  {
    return  strcmp(a,b);
}
char* create_string(char* line)  {
    char* str;
    str=malloc(200*sizeof(char));
    strcpy(str,line);
    return str;
}
int main(void)  {
    Set memory;
    SetNode node;
    char line[200],flag;
    memory=set_create(compare_strings,free); // δημιουργουμε ενα συνολο που ταξινομει συμβολοσειρες βαση της strcmp 
    while (fgets(line,200,stdin)!=NULL)  {
        flag=1;
        if (line[0]!='\n')  {  // δε θελουμε να κατοχωρηθει το Enter σε περιπτωση διπλου πατηματος
            if ((node=set_first(memory))!=SET_EOF)  {  //αν η γραμμη που διαβασαμε υπαρχει στην εισοδο 
                while (node!=SET_EOF)  {
                    if (strcmp((char*)set_node_value(memory,node),line)>=0)  { // οταν βρουμε μια συμβολοσειρα που εινια μεγαλυτερη η ιση απο αυτη που διαβασαμε
                        puts((char*)set_node_value(memory,node));      // τοτε την εκτυπωνουμε (ζητουμενο ασκησης)
                        flag=0;
                        break;
                    }
                    else  {
                        node=set_next(memory,node);
                    }
                }
                if (flag==1)  {
                    printf("<none>\n");  // αν δε βρεθει σθμβολοσειρα που να πληρει τις προυποθεσεις τοτε εκτυπωνουμε none
                }
            }  
            else  {
                printf("<none>\n");
            }
            set_insert(memory,create_string(line)); //καταχωρει τη συμβολοσειρα στο συνολο , αν υπαρχει ηδη τοτε δεν αλλαζει τιποτα 
        }
    }
    set_destroy(memory);  //αποδεσμευση ολης της μνημης
    return 0;
}