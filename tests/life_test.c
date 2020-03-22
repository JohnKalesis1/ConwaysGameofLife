//#include "acutest.h"
#include <stdio.h>
#include <stdlib.h>
#include "life.h"
#define VALUE 5
#define NEWVALUE 5
int main(void)  {
    LifeState Universe;
    char *file="tests.txt";
    LifeCell Cell;
    MapNode Node;
    Universe=life_create_from_rle(file);
    Node=map_first(Universe);
    Node=map_next(Universe,Node);
    /*while (Node !=MAP_EOF)  {
        //Cell=(LifeCell*)map_node_key(Universe,Node);
       // printf("x=%d y=%d ",Cell->x,Cell->y);
        Node=map_next(Universe,Node);
    
    }
    for (int i=0;i<100;i++)  {
        Cell.x=i;
        if (life_get_cell(Universe,Cell)==true) {
            printf("%d ",i);
        }
    }*/
    printf("size %d",map_size(Universe));
    //life_save_to_rle(Universe,file);
   // TEST_CHECK(map_size(Universe)==VALUE);
    //Universe=life_evolve(Universe);
    //TEST_CHECK(map_size(Universe)==NEWVALUE);
}
/*TEST_LIST = {
	{ "test_life_test", life_test },

	{ NULL} // τερματίζουμε τη λίστα με NULL
};*/