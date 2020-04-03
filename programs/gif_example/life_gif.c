#include "bmp.h"
#include "gif.h"
#include "life.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
	int top=atoi(argv[2]),down=atoi(argv[4]),left=atoi(argv[3]),right=atoi(argv[5]); //ορια που να δειξει στο gif
	float zoom=atof(argv[7]); //βαθμος μεγενθυσης
	int y_size = round(zoom)*(top-down);
	int x_size= round(zoom)*(right-left);
	int cell_size = 0;
	if (zoom>1)  {
		cell_size=round(zoom)-1;
	}
	else  if (zoom<1)  {

	}
	GIF* gif = gif_create(x_size, y_size);
	Bitmap* bitmap = bm_create(x_size, y_size);
	LifeState state,Universe;
	LifeCell Cell;
    List list;
    ListNode loop,lnode;
    lnode=LIST_BOF;
	int steps=atoi(argv[8]); //αλματα ανα εξελιξη που να γινονται
	int frames=atoi(argv[6])*steps; // με στοχο να παραχθουν οσα frames εχουν ζητηθει απο το χρηστη , πρεπει να γινουν frames*steps εξελιξεις 
	int temp=steps;
	SetNode snode;
    Universe=life_create_from_rle(argv[1]);
	list=life_evolve_many(Universe,frames,&loop);
	gif->default_delay = atoi(argv[9]);
	unsigned int palette[] = { 0xFF000000, 0xFFFFFFFF };
	gif_set_palette(gif, palette, 2);
	bm_set_color(bitmap, bm_atoi("black"));
	bm_clear(bitmap);
	bm_set_color(bitmap, bm_atoi("white"));
	snode=set_first(Universe);
	while (snode!=SET_EOF)  { //εμφανιση της αχικης καταστασης 
		Cell=*(LifeCell*) set_node_value(Universe,snode); //για καθε ζωντανο κυτταρο που βρισκεται εντος των οριων του πινακα ,μεγενθυμενου ή οχι
		if (round(zoom)*Cell.x<right && round(zoom)*Cell.x>left && round(zoom)*Cell.y<top && round(zoom)*Cell.y>down)  { // χρωματιζουμε το κελι και την αντιστοιχη περιφερεια που ζητατε ασπρο
			bm_fillrect(bitmap, round(zoom)*abs(Cell.x-left), round(zoom)*abs(top-Cell.y), round(zoom)*abs(Cell.x-left)+cell_size,round(zoom)*abs(top-Cell.y)+cell_size);
		}
		snode=set_next(Universe,snode);
	}
	gif_add_frame(gif, bitmap);
	lnode=list_first(list);
	while (temp--!=1)  {
		lnode=list_next(list,lnode); //διαδικασια αλματος εξελιξεων , που ουσιαστικα ειναι προσπελαση της λιστας οσες φορες ζητατε
		if (lnode==LIST_EOF)  {
				break;  // αν φτασουμε στο τελος της λιστας , τοτε σταματαμε
			}
	}
	for(int i = 0; i < frames/steps; i++) {
		bm_set_color(bitmap, bm_atoi("black"));
		bm_clear(bitmap);
		bm_set_color(bitmap, bm_atoi("white"));
		if (lnode==LIST_EOF && loop!=NULL)  { //αμα σε προηγουμενο αλμα εχουμε φτασει στο τελος της λιστας , σημαινει οτι θα υπαρχει επναληψη (δλδ μικροτερο μεγεθος λιστας)
			lnode=loop; //και για αυτο θα παμε πισω στο κομβο που αρχιζει η επαναληψη
		}
		state=list_node_value(list,lnode);
		snode=set_first(state);
		while (snode!=SET_EOF)  {
			Cell=*(LifeCell*) set_node_value(state,snode); //για καθε ζωντανο κυτταρο που βρισκεται ενοτς των οριων του πινακα
			if (round(zoom)*Cell.x<=right && round(zoom)*Cell.x>=left && round(zoom)*Cell.y<=top && round(zoom)*Cell.y>=down)  {
				bm_fillrect(bitmap, round(zoom)*abs(Cell.x-left), round(zoom)*abs(top-Cell.y), round(zoom)*abs(Cell.x-left)+cell_size,round(zoom)*abs(top-Cell.y)+cell_size);
			}		
			snode=set_next(state,snode);
		}
		temp=steps;
		while(temp--!=0)  {
			lnode=list_next(list,lnode);
			if (lnode==LIST_EOF)  {
				break;
			}
		}
		gif_add_frame(gif, bitmap);
	}
	life_destroy(Universe);
	lnode=list_first(list);
	for (int i=0;i<frames;i++)  {
		life_destroy(list_node_value(list,lnode));
		lnode=list_next(list,lnode);
	}
	list_destroy(list); //αποδεσμεση ολης της μνημης 
	gif_save(gif, argv[10]);
	bm_free(bitmap);
	gif_free(gif);
}
