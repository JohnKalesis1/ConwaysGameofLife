#include <stdio.h>
#include <stdlib.h>
#include "life.h"
#include <string.h>
int main(void)  {
    LifeState Universe;
    char text[500];
    char *light_spaceship="../programs/Game_Life_Gif/lightweight_spaceship.txt";
    char *glider="../programs/Game_Life_Gif/glider.txt";
    char *period_5_oscillator="../programs/Game_Life_Gif/period_5_oscillator.txt";
    char *period_2_oscillator="../programs/Game_Life_Gif/period_2_oscillator.txt";
    char *file="tests.txt";
    FILE *fp;
    Universe=life_create_from_rle(light_spaceship);
    life_save_to_rle(Universe,file);
    fp=fopen(file,"r");
    fscanf(fp,"%s",text);
    if (strcmp(text,"bo2bo$o$o3bo$4o!")!=0)  {
        printf("Error in function\n");
    }
    else  {
        printf("Passed \n");
    }
    fclose(fp);
    Universe=life_create_from_rle(period_5_oscillator);
    life_save_to_rle(Universe,file);
    fp=fopen(file,"r");
    fscanf(fp,"%s",text);
    if (strcmp(text,"4b2o6b2o$3bobo6bobo$3bo10bo$2obo10bob2o$2obobo2b2o2bobob2o$3bobobo2bobobo$3bobobo2bobobo$2obobo2b2o2bobob2o$2obo10bob2o$3bo10bo$3bobo6bobo$4b2o6b2o!")!=0)  {
        printf("Error in function\n");
    }
    else  {
        printf("Passed \n");
    }
    fclose(fp);
    Universe=life_create_from_rle(period_2_oscillator);
    life_save_to_rle(Universe,file);
    fp=fopen(file,"r");
    fscanf(fp,"%s",text);
    if (strcmp(text,"3o!")!=0)  {
        printf("Error in function\n");
    }
    else  {
        printf("Passed \n");
    }
    fclose(fp);
    Universe=life_create_from_rle(glider);
    life_save_to_rle(Universe,file);
    fp=fopen(file,"r");
    fscanf(fp,"%s",text);
    if (strcmp(text,"bo$2bo$3o!")!=0)  {
        printf("Error in function\n");
    }
    else  {
        printf("Passed \n");
    }
    fclose(fp);
}