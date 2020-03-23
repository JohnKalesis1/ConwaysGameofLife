//#include "acutest.h"
#include <stdio.h>
#include <stdlib.h>
#include "life.h"
#define VALUE 5
#define NEWVALUE 5
int main(void)  {
    LifeState Universe;
    char *file="tests.txt";
    Universe=life_create_from_rle(file);
    life_save_to_rle(Universe,"out_test.txt");
    //printf("size %d",map_size(Universe));
    //life_save_to_rle(Universe,file);
   // TEST_CHECK(map_size(Universe)==VALUE);
    //Universe=life_evolve(Universe);
    //TEST_CHECK(map_size(Universe)==NEWVALUE);
}
/*TEST_LIST = {
	{ "test_life_test", life_test },

	{ NULL} // τερματίζουμε τη λίστα με NULL
};*/