/////////////////////////////////////////////////////////////////////////
//
// Παράδειγμα δημιουργίας ενός GIF χρησιμοποιώντας τη βιβλιοθήκη libbmp
//
///////////////////////////////////////////////////////////////////////// 

#include "bmp.h"
#include "gif.h"
#include "life.h"

int main(int argc, char *argv[]) {
	// Μεγέθη
	int size = 128;
	int cell_size = 0;

	// Δημιουργία ενός GIF και ενός bitmap στη μνήμη
	GIF* gif = gif_create(size, size);
	Bitmap* bitmap = bm_create(size, size);
	LifeState state,Universe;
	LifeCell Cell;
    List list;
    ListNode ptr,lnode;
    lnode=LIST_BOF;
	int steps=150;
    char *file="tests.txt";
	SetNode snode;
    Universe=life_create_from_rle(file);
	list=life_evolve_many(Universe,steps,&ptr);
	// Default καθυστέρηση μεταξύ των frames, σε εκατοστά του δευτερολέπτου
	gif->default_delay = 10;
	lnode=list_first(list);
	// Δημιουργούμε ενα animation με ένα "cell" το οποίο μετακινείται από τη δεξιά-πάνω
	// γωνία προς την κάτω-αριστερά. Το cell μετακινείται ένα pixel τη φορά, οπότε το animation
	// θα έχει τόσα frames όσα το μέθεθος της εικόνας.
	unsigned int palette[] = { 0xFF000000, 0xFFFFFFFF }; // black, white
	gif_set_palette(gif, palette, 2);
	for(int i = 0; i < steps; i++) {
		// Σε κάθε frame, πρώτα μαυρίζουμε ολόκληρο το bitmap
		bm_set_color(bitmap, bm_atoi("black"));
		bm_clear(bitmap);

		// Και μετά ζωγραφίζουμε ένα άσπρο τετράγωνο με αρχή το
		// σημείο (i,i) και τέλος το (i+cell_size, i+cell_size)
		
		bm_set_color(bitmap, bm_atoi("white"));
		state=list_node_value(list,lnode);
		snode=set_first(state);
		while (snode!=SET_EOF)  {
			Cell=*(LifeCell*) set_node_value(state,snode);
			bm_fillrect(bitmap, Cell.x+size/2, Cell.y+size/2, Cell.x+size/2+cell_size, Cell.y+size/2+cell_size);
			snode=set_next(state,snode);
		}
		lnode=list_next(list,lnode);
		// Τέλος προσθέτουμε το bitmap σαν frame στο GIF (τα περιεχόμενα αντιγράφονται)
		gif_add_frame(gif, bitmap);
	}

	// Αποθήκευση σε αρχείο
	gif_save(gif, "example.gif");

	// Αποδέσμευση μνήμης
	bm_free(bitmap);
	gif_free(gif);
}
