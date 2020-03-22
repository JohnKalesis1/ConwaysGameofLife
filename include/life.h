#include "common_types.h"
#include "ADTMap.h" 
typedef struct {
    int x;
    int y;
} LifeCell ;
typedef Map LifeState;
LifeState life_create();
LifeState life_create_from_rle(char* file);
void life_save_to_rle(LifeState state, char* file);
bool life_get_cell(LifeState state, LifeCell cell);
void life_set_cell(LifeState state, LifeCell cell, bool value);
LifeState life_evolve(LifeState state);
void life_destroy(LifeState state);