#include<stdio.h>
#include<string.h>
typedef struct node {
	char *name;
	char *last;
	int pnrno;
	int tno;
	int ticket;
	float fare;
	char *train;
	char *from;
	char *to;
	int dd, mm, yy;
	char *atime;
	char *dtime;
	struct node *next;
	struct node *prev;
}node;
typedef struct list {
	struct node *head;
	struct node *tail;
}list;
