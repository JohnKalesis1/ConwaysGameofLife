#include <stdlib.h>
#include <stdio.h>
#include "pq_sort.h"
#include "ADTPriorityQueue.h"

void pq_sort_vector(Vector vec, CompareFunc compare) {
	DestroyFunc old_destroy = vector_set_destroy_value(vec, NULL);
	PriorityQueue pqueue = pqueue_create(compare,NULL,vec);
	int i;
	for (i=vector_size(vec)-1;i>=0;i--)  {   // αρχιζω απο το τελος του πινακα και ανα βημα κατευθυνομαι στην αρχη τοποθετωντας στοιχεια
		vector_set_at(vec,i,pqueue_max(pqueue)); // βαζω το μεγαλυτερο στοιχειο της ουρας στην θεση που δειχνει το i
		pqueue_remove_max(pqueue);
	}
	pqueue_destroy(pqueue);
	vector_set_destroy_value(vec, old_destroy);
}

void pq_sort_list(List list, CompareFunc compare) {
	DestroyFunc old_destroy = list_set_destroy_value(list, NULL);
	PriorityQueue pqueue = pqueue_create(compare,NULL,NULL);
	ListNode node=list_first(list);
	int i,temp;
	for (i=0;i<list_size(list);i++)  {
		pqueue_insert(pqueue,list_node_value(list,node)); // δημιουργω μια ουρα προτεαραιοτητας με τα στοιχεια της λιστας
		node=list_next(list,node);		
	}
	for (i=list_size(list)-1;i>=0;i--)  {
		temp=i-1;
		if (i==0)  {
			node=LIST_BOF;  // οταν φτασω στο πρωτο για να μπορεσω να το διαγραψω πρεπει να καλεσω remove_next απο τον προηγουμενο κομβο δλδ LIST_BOF
		}
		else  {
			node=list_first(list);
			while (temp-->0)  {			// απο το τελος γεμιζω τη λιστα  
				node=list_next(list,node);
			}
		}
		list_remove_next(list,node);     // διαγραφω το υπαρχων στοιχειο 
		list_insert_next(list,node,pqueue_max(pqueue));  // και στη θεση του βαζω το πρωτο της ουρας προτεραιοτητας
		pqueue_remove_max(pqueue);
	}
	pqueue_destroy(pqueue);
	list_set_destroy_value(list, old_destroy);
}
