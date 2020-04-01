#include "bmp.h"
#include "gif.h"
#include "life.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int top=atoi(argv[2]),down=atoi(argv[4]),left=atoi(argv[3]),right=atoi(argv[5]);
	int y_size = top-down;
	int x_size= right-left;
	int cell_size = 0;
	GIF* gif = gif_create(x_size, y_size);
	Bitmap* bitmap = bm_create(x_size, y_size);
	LifeState state,Universe;
	LifeCell Cell;
    List list;
    ListNode loop,lnode;
    lnode=LIST_BOF;
	int steps=atoi(argv[6]);
	int jump=atoi(argv[8]);
	int temp=jump;
	SetNode snode;
    Universe=life_create_from_rle(argv[1]);
	list=life_evolve_many(Universe,steps,&loop);
	gif->default_delay = atoi(argv[9]);
	unsigned int palette[] = { 0xFF000000, 0xFFFFFFFF };
	gif_set_palette(gif, palette, 2);
	bm_set_color(bitmap, bm_atoi("black"));
	bm_clear(bitmap);
	bm_set_color(bitmap, bm_atoi("white"));
	snode=set_first(Universe);
	while (snode!=SET_EOF)  {
		Cell=*(LifeCell*) set_node_value(Universe,snode);
		if (Cell.x<right && Cell.x>left && Cell.y<top && Cell.y>down)  {
			bm_fillrect(bitmap, Cell.x-left, Cell.y-down, Cell.x-left+cell_size, Cell.y-down+cell_size);
		}
		snode=set_next(Universe,snode);
	}
	gif_add_frame(gif, bitmap);
	lnode=list_first(list);
	while (temp--!=1)  {
		lnode=list_next(list,lnode);
	}
	for(int i = 0; i < steps; i++) {
		bm_set_color(bitmap, bm_atoi("black"));
		bm_clear(bitmap);
		bm_set_color(bitmap, bm_atoi("white"));
		if (lnode==LIST_EOF && loop!=NULL)  {
			lnode=loop;
		}
		state=list_node_value(list,lnode);
		snode=set_first(state);
		while (snode!=SET_EOF)  {
			Cell=*(LifeCell*) set_node_value(state,snode);
			if (Cell.x<right && Cell.x>left && Cell.y<top && Cell.y>down)  {
				bm_fillrect(bitmap, Cell.x-left, Cell.y-down, Cell.x-left+cell_size, Cell.y-down+cell_size);
			}		
			snode=set_next(state,snode);
		}
		temp=jump;
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
	for (int i=0;i<steps;i++)  {
		life_destroy(list_node_value(list,lnode));
		lnode=list_next(list,lnode);
	}
	list_destroy(list);
	gif_save(gif, argv[10]);
	bm_free(bitmap);
	gif_free(gif);
}
