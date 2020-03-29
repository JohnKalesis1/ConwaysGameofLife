#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTMap.h"
int compare_strings(Pointer a,Pointer b)  {
    return  strcmp(a,b);
}
int* create_int(int x)  {
    int *ptr;
    ptr=malloc(sizeof(int));
    *ptr=x;
    return ptr;
}
char* create_string(char* line)  {
    char* str;
    str=malloc(20*sizeof(char));
    strcpy(str,line);
    return str;
}
int main(void)  {
    char line[20];
    int val;
    Map map;
    map=map_create(compare_strings,free,free);
    while (fgets(line,20,stdin)!=NULL)  {
        if (line[0]!='\n')  {
            if (map_find_node(map,line)!=MAP_EOF)  {
                val=*(int*)map_node_value(map,map_find_node(map,line))+1;
                //map_remove(map,line); //δεν ειμαι σιγουρος αν αλλαζει κατι , αλλα το χω βαλει 
                map_insert(map,create_string(line),create_int(val));
            }
            else  {
                val=0;
                map_insert(map,create_string(line),create_int(val));
            }
            printf("%s Line occurence : %d \n",line,* (int*) map_node_value(map,map_find_node(map,line)));
        }
    }
    map_destroy(map);
}