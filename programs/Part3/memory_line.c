#include <stdio.h>
#include "ADTSet.h"
#include <string.h>
#include <stdlib.h>
int compare_strings(Pointer a,Pointer b)  {
    return  strcmp(a,b);
}
int main(void)  {
    Set memory;
    SetNode node;
    int i,line_counter;
    char line[200],flag,**line_holder;
    memory=set_create(compare_strings,NULL);
    line_holder=malloc(1000000*sizeof(char*));
    for (i=0;i<1000000;i++)  {
        line_holder[i]=malloc(200*sizeof(char));
    }
    line_counter=0;
    while (fgets(line,200,stdin)!=NULL)  {
        flag=1;
        if (line[0]!='\n')  {
            strcpy(line_holder[line_counter],line);
            if ((node=set_first(memory))!=SET_EOF)  {
                while (node!=SET_EOF)  {
                    if (strcmp((char*)set_node_value(memory,node),line_holder[line_counter])>=0)  {
                        puts((char*)set_node_value(memory,node));
                        flag=0;
                        break;
                    }
                    else  {
                        node=set_next(memory,node);

                    }
                }
                if (flag==1)  {
                    printf("<none>\n");
                }
            }  
            else  {
                printf("<none>\n");
            }
            set_insert(memory,line_holder[line_counter]);
            line_counter++;
        }
    }
    set_destroy(memory);
    for (i=0;i<1000000;i++)  {
        free(line_holder[i]);
    }
    free(line_holder);
    return 0;
}