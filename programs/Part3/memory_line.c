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
    memory=set_create(compare_strings,free);
    while (fgets(line,200,stdin)!=NULL)  {
        flag=1;
        if (line[0]!='\n')  {
            if ((node=set_first(memory))!=SET_EOF)  {
                while (node!=SET_EOF)  {
                    if (strcmp((char*)set_node_value(memory,node),line)>=0)  {
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
            set_insert(memory,create_string(line));
        }
    }
    set_destroy(memory);
    return 0;
}