#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTMap.h"
int main(void)  {
    char line[20],**line_holder;
    int val,*nval,line_counter=0;;
    Map map;
    line_holder=malloc(1000000*sizeof(char*));
    nval=malloc(1000000*sizeof(int*));
    for (val=0;val<1000000;val++)  {
        line_holder[val]=malloc(20*sizeof(char));
    }
    val=0;
    map=map_create((void*)strcmp,NULL,NULL);
    while (fgets(line,20,stdin)!=NULL)  {
        if (line[0]!='\n')  {
            strcpy(line_holder[line_counter],line);
            if ((map_find_node(map,(void*)line_holder[line_counter]))!=MAP_EOF)  {
                nval[line_counter]=*(int*)map_node_value(map,map_find_node(map,(void*)line_holder[line_counter]))+1;
                map_insert(map,(void*)line_holder[line_counter],&nval[line_counter]);
            }
            else  {
                val=0;
                map_insert(map,line_holder[line_counter],&val);
            }
            printf("%s Line occurence : %d \n",line,* (int*) map_node_value(map,map_find_node(map,(void*)line_holder[line_counter])));
            line_counter++;
        }
    }
    free(nval);
    for (val=0;val<1000000;val++)  {
        free(line_holder[val]);
    }
    free(line_holder);
    map_destroy(map);
    return 0;
}