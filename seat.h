#include<stdio.h>
typedef struct availabity {
	int total_ticket;
	int upper;
	int middle;
	int lower;
	int waiting;
}available;
typedef struct node {
		int ticketav;
		int ticketup;
		int ticketmi;
		int ticketlo;
		int ticketwa;
		struct node *prev;
		struct node *next;
	}node;
typedef struct list {
	struct node *head, *tail;	
}list;
