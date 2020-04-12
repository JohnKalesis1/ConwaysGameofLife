#include <stdio.h>
#include <stdlib.h>
#include "life.h"
#include <string.h>
int compare_states(Pointer a,Pointer b);
int main(void)  {
    LifeState Universe;
    List list;
    ListNode node;
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
    fscanf(fp,"%s",text); //βασικος ελεγχος για σωστη η αντιγραφη στοιχειων απο κειμενο και σε κειμενο 
    if (strcmp(text,"4b2o6b2o$3bobo6bobo$3bo10bo$2obo10bob2o$2obobo2b2o2bobob2o$3bobobo2bobobo$3bobobo2bobobo$2obobo2b2o2bobob2o$2obo10bob2o$3bo10bo$3bobo6bobo$4b2o6b2o!")!=0)  {
        printf("Error in function\n");
    }
    else  {
        printf("Passed \n");
        list=life_evolve_many(Universe,6,&node);
        ListNode lnode=list_first(list);
        int i=4;
        while (i--!=0)  {
            lnode=list_next(list,lnode);
        }
        LifeState U=list_node_value(list,lnode); //δουλευει και η συναρτηση πολλαπλης εξελιξης 
        if (compare_states(Universe,U)==0)  {   //καθως μετα απο πεντε εξελιξεις επιστρεφουμε στην αρχικη μορφη
            printf("Passed \n");
            lnode=list_first(list);
            LifeState U=list_node_value(list,lnode);
            LifeState Y =list_node_value(list,node);
            if (compare_states(Y,U)==0)  {
                printf("Passed \n"); //δουλευει η καταχωρηση της επαναληψης σε κομβο 
            }                        //δηλαδη το πρωτο στοιχειο που παρατηρηθηκε η επαναληψη , αποθηεκευεται σε εναν κομβο
            else  {
            printf("Error \n");
        }
        }
        else  {
            printf("Error \n");
        }
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
        list=life_evolve_many(Universe,2,&node);
        ListNode lnode=list_first(list);
        lnode=list_next(list,lnode);
        LifeState U=list_node_value(list,lnode);
        if (compare_states(Universe,U)==0)  {
            printf("Passed \n");
            Universe=life_evolve(Universe);
            life_save_to_rle(Universe,file);
            fp=fopen(file,"r");
            fscanf(fp,"%s",text);
            if (strcmp("o$o$o!",text)==0)  { //δουλευει η εξελιξη σε επομενο σταδιο 
                printf("Passed \n");
            }
            else  {
                printf("Error \n");
            }
        }
        else  {
            printf("Error \n");
        }
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
        list=life_evolve_many(Universe,5,&node);
        ListNode lnode=list_first(list);
        int i=3;
        while (i--!=0)  {
            lnode=list_next(list,lnode);
        }
        LifeState U=list_node_value(list,lnode);
        life_save_to_rle(U,file);
        fp=fopen(file,"r");
        fscanf(fp,"%s",text);
        if (strcmp("bo$2bo$3o!",text)==0 && compare_states(U,Universe)!=0)  { //το glider εχει μετακινηθει επιτυχως στο χωρο 
            printf("Passed \n");                    //και εχει παρει την ιδια μορφη (στο rle φαινεται αυτο) οπως θα επρεπε
        }
        else  {
            printf("Error \n");
        }
        
    }
    fclose(fp);

}