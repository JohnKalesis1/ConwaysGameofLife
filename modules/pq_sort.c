////////////////////////////////
//
// Υλοποίηση του pq_sort module
//
////////////////////////////////

#include <stdlib.h>

#include <stdio.h>
#include "pq_sort.h"
#include "ADTPriorityQueue.h"

void pq_sort_vector(Vector vec, CompareFunc compare) {
	// Προσοχή! Μέσα στη συνάρτηση αυτή θα χρειαστεί να αντικαταστήσουμε τα περιεχόμενα του vector. Δε
	// θέλουμε όμως όσο το κάνουμε αυτό το vector να καλέσει τη destroy! Οπότε αλλάζουμε προσωρινά τη
	// συνάρτηση destroy σε NULL (αποθηκεύοντας την παλιά τιμή).
	DestroyFunc old_destroy = vector_set_destroy_value(vec, NULL);
	PriorityQueue pqueue = pqueue_create(compare,NULL,vec);
	int i;
	for (i=vector_size(vec)-1;i>=0;i--)  {
		vector_set_at(vec,i,pqueue_max(pqueue));
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
		pqueue_insert(pqueue,list_node_value(list,node));
		
		node=list_next(list,node);
		
	}
	for (i=list_size(list)-1;i>=0;i--)  {
		temp=i-1;
		if (i==0)  {
			node=LIST_BOF;
		}
		else  {
			node=list_first(list);
			while (temp-->0)  {
				node=list_next(list,node);
			}
		}
		list_remove_next(list,node);
		list_insert_next(list,node,pqueue_max(pqueue));
		pqueue_remove_max(pqueue);
	}
	pqueue_destroy(pqueue);
	list_set_destroy_value(list, old_destroy);
}
