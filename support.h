#include<stdio.h>
typedef struct fake {
	int dd, mm, yy;
}fake;
typedef struct hira {
	int trainno;
	char *train_name;
	char *notice;
	int time;
	int dd, mm, yy;
	struct hira *next;
	struct hira *prev; 
}hira;
typedef struct list1 {
	struct hira *head , *tail;
}list1;

typedef struct info {
	int trainno;
	char train_name[20];
	char notice[20];
	int time;
	int dd, mm, yy;
}info;
