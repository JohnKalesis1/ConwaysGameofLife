//#include "acutest.h"
#include <stdio.h>
#include <stdlib.h>
#include "life.h"
int main(void)  {
    LifeState Alt_Universe,Universe;
    List list;
    int steps=5;
    ListNode ptr,lnode;
    lnode=LIST_BOF;
    char *file="tests.txt";
    Universe=life_create_from_rle(file);
    /*Universe=life_evolve(Universe);
    life_save_to_rle(Universe,"out_test.txt");*/
    /*Alt_Universe=life_evolve(Universe);
    Alt_Universe=life_evolve(Alt_Universe);
    if (compare_states(Alt_Universe,Universe)==0)  {
        printf("check\n");
    }
    if (compare_states(Universe,Universe)==0)  {
        printf("check finished\n");
    }*/
    list=life_evolve_many(Universe,steps,&ptr);
    lnode=list_first(list);
    lnode=list_next(list,lnode);
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