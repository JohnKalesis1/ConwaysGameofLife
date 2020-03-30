//#include "acutest.h"
#include <stdio.h>
#include <stdlib.h>
#include "life.h"
#define VALUE 5
#define NEWVALUE 5
int main(void)  {
    LifeState Universe;
    List list;
    int steps=2;
    ListNode *ptr,lnode;
    char *file="tests.txt";
    Universe=life_create_from_rle(file);
    //Universe=life_evolve(Universe);
    list=life_evolve_many(Universe,steps,ptr);
    lnode=list_first(list);
    while (steps--!=1)  {
        lnode=list_next(list,lnode);
    }
    life_save_to_rle((LifeState)list_node_value(list,lnode),"out_test.txt");
    //life_save_to_rle(Universe,"out_test.txt");
   // TEST_CHECK(map_size(Universe)==VALUE);
    //Universe=life_evolve(Universe);
    //TEST_CHECK(map_size(Universe)==NEWVALUE);
}
/*TEST_LIST = {
	{ "test_life_test", life_test },

	{ NULL} // τερματίζουμε τη λίστα με NULL
};*/