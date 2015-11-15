/*****************************************************************************
 * Copyright (C) GAURANG N. JUNGARE gaurangjungare24@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 *****************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "traveller.h"
#include "link.h"
#include "login.h"
#include "support.h"
ticket pnr_status(int pnrno) {
	ticket K, fair;
	int s = 0;
	FILE *fp, *fd;
	fp = fopen("ticket2.txt", "rb+");
	fd = fopen("available.txt", "rb+");
	while(fread(&K, sizeof(ticket), 1, fp) == 1) {
		if(K.pnrno == pnrno) {
			s = 1;
			fair = K;
			return fair;
		}
	}
}
void init(list *l) {
	l->head = NULL;
	l->tail = NULL;
}
ticket cancellation(int pnrno, char *name, char *last) {
	int i = 0, count = 0;
	FILE *fp, *fd;
	list *l;
	fp = fopen("ticket2.txt", "rb+");
	fd = fopen("cancelled.txt", "ab+");
	ticket T, q, copy, A;
	node *P, *r, *w;
	
	l = (list *)malloc(sizeof(list));
	while(fread(&T, sizeof(ticket), 1, fp) == 1) {
		P = (node *)malloc(sizeof(node));
		P->name = (char *)malloc(sizeof(char) * 18);
		P->last = (char *)malloc(sizeof(char) * 18);
		P->train = (char *)malloc(sizeof(char) * 28);
		P->atime = (char *)malloc(sizeof(char) * 18);
		P->dtime = (char *)malloc(sizeof(char) * 18);
		P->from = (char *)malloc(sizeof(char) * 18);
		P->to = (char *)malloc(sizeof(char) * 18);
		strcpy(P->name, T.firstname);
		strcpy(P->last, T.lastname);
		strcpy(P->train, T.train_name);
		strcpy(P->atime, T.arrivaltime);
		strcpy(P->dtime, T.departuretime);
		strcpy(P->from, T.from);
		strcpy(P->to, T.to);
		P->pnrno = T.pnrno;
		P->dd = T.dd;
		P->mm = T.mm;
		P->yy = T.yy;
		P->ticket = T.no_of_ticket;
		P->tno = T.trainno1;
		P->fare = T.fare;
		if(count == 0) {
			init(l);
		}
		if(l->head == NULL) {
			l->head = P;
			l->tail = P;
			P->next = NULL;
			P->prev = NULL;
		}
		else {
			P->prev = l->tail;
			P->next = NULL;
			l->tail->next = P;
			l->tail = l->tail->next;
		}
		if(P->pnrno == pnrno) {
			if((strcmp(P->name, name) == 0) && (strcmp(P->last, last) == 0)) {
				
				strcpy(q.firstname, P->name);
				strcpy(q.lastname, P->last);
				strcpy(q.train_name, P->train);
				strcpy(q.arrivaltime, P->atime);
				strcpy(q.departuretime, P->dtime);
				strcpy(q.from, P->from);
				strcpy(q.to, P->to);
				q.fare = P->fare;
				q.pnrno = P->pnrno;
				q.dd = P->dd;
				q.mm = P->mm;
				q.yy = P->yy;
				q.no_of_ticket = P->ticket;
				q.trainno1 = P->tno;
				
				if((P->prev == NULL) && (P->next == NULL)) {
					l->head = NULL;
					l->tail = NULL;
					free(P);
					copy = q;
					fwrite(&q, sizeof(ticket), 1, fd);
					//return q;
				}
				else if((P->prev == NULL) && (P->next != NULL))  {
					P = P->next;
					P->prev->next = NULL;
				 	P->prev = NULL;
					l->head = P;
					copy = q;
					fwrite(&q, sizeof(ticket), 1, fd);
				}
				else {
					w = P;
					P->prev->next = NULL;
					l->tail = l->tail->prev;
					P->prev = NULL;
					P = l->tail;
					free(w);
					copy = q;
					fwrite(&q, sizeof(ticket), 1, fd);
					//return (q);
				}
			}
		}		 
		count++;
	}
	fclose(fp);
	fclose(fd);
	fp = fopen("ticket2.txt", "wb+");
	r = l->head;
	while(r->next != NULL) {
		//printf("###########\n");
		//printf("%d\n", r->pnrno);
		strcpy(A.firstname, r->name);
		strcpy(A.lastname,r->last);
		strcpy(A.train_name, r->train);
		strcpy( A.departuretime, r->dtime);
		strcpy(A.from, r->from);
		strcpy(A.to, r->to);
		A.fare = r->fare;
		A.pnrno = r->pnrno;
		A.dd = P->dd;
		A.mm = P->mm;
		A.yy = P->yy;
		A.no_of_ticket = r->ticket;
		A.trainno1 = r->tno;
		//printf("%d\n", A.trainno1);
		fwrite(&A, sizeof(ticket), 1, fp);
		r = r->next;
	}
	if(r->next == NULL) {
		//printf("%d\n", r->pnrno);
		strcpy(A.firstname, r->name);
		strcpy(A.lastname,r->last);
		strcpy(A.train_name, r->train);
		strcpy(A.arrivaltime, r->atime);
		strcpy( A.departuretime, r->dtime);
		strcpy(A.from, r->from);
		strcpy(A.to, r->to);
		A.fare = r->fare;
		A.pnrno = r->pnrno;
		A.dd = P->dd;
		A.mm = P->mm;
		A.yy = P->yy;
		A.no_of_ticket = r->ticket;
		A.trainno1 = r->tno;
		//printf("%d\n", A.trainno1);
		fwrite(&A, sizeof(ticket), 1, fp);
	}
	fclose(fp);
	return copy; 
}	
ticket refund(int pnrno) {
	int i = 0, count = 0;
	char user[15], pass[15];
	ticket T, q, copy, A;
	traveller valid;
	node *P, *r, *w;
	list *l;
	FILE *fp, *fs;
	fp = fopen("cancelled.txt", "ab+");
	fs = fopen("login2.txt", "rb+");
	l = (list *)malloc(sizeof(list));
	while(fread(&T, sizeof(ticket), 1, fp) == 1) {
		P = (node *)malloc(sizeof(node));
		P->name = (char *)malloc(sizeof(char) * 18);
		P->last = (char *)malloc(sizeof(char) * 18);
		P->train = (char *)malloc(sizeof(char) * 28);
		P->atime = (char *)malloc(sizeof(char) * 18);
		P->dtime = (char *)malloc(sizeof(char) * 18);
		P->from = (char *)malloc(sizeof(char) * 18);
		P->to = (char *)malloc(sizeof(char) * 18);
		strcpy(P->name, T.firstname);
		strcpy(P->last, T.lastname);
		strcpy(P->train, T.train_name);
		strcpy(P->atime, T.arrivaltime);
		strcpy(P->dtime, T.departuretime);
		strcpy(P->from, T.from);
		strcpy(P->to, T.to);
		P->pnrno = T.pnrno;
		P->dd = T.dd;
		P->mm = T.mm;
		P->yy = T.yy;
		P->ticket = T.no_of_ticket;
		P->tno = T.trainno1;
		P->fare = T.fare;
		if(count == 0) {
			init(l);
		}
		if(l->head == NULL) {
			l->head = P;
			l->tail = P;
			P->next = NULL;
			P->prev = NULL;
		}
		else {
			P->prev = l->tail;
			P->next = NULL;
			l->tail->next = P;
			l->tail = l->tail->next;
		}
			if(T.pnrno == pnrno) {
				strcpy(q.firstname, P->name);
				strcpy(q.lastname, P->last);
				strcpy(q.train_name, P->train);
				strcpy(q.arrivaltime, P->atime);
				strcpy(q.departuretime, P->dtime);
				strcpy(q.from, P->from);
				strcpy(q.to, P->to);
				q.fare = P->fare;
				q.pnrno = P->pnrno;
				q.dd = P->dd;
				q.mm = P->mm;
				q.yy = P->yy;
				q.no_of_ticket = P->ticket;
				q.trainno1 = P->tno;
				if((P->prev == NULL) && (P->next == NULL)) {
					l->head = NULL;
					l->tail = NULL;
					free(P);
					copy = q;
					//return q;
				}
				else if((P->prev == NULL) && (P->next != NULL))  {
					P = P->next;
					P->prev->next = NULL;
				 	P->prev = NULL;
					l->head = P;
					copy = q;
				}
				else {
					w = P;
					P->prev->next = NULL;
					l->tail = l->tail->prev;
					P->prev = NULL;
					P = l->tail;
					free(w);
					copy = q;
					//return (q);
				}
			}
				 
		count++;
	}
	fclose(fp);
	fclose(fs);
	fp = fopen("cancelled.txt", "wb+");
	r = l->head;
	while(r->next != NULL) {
		strcpy(A.firstname, r->name);
		strcpy(A.lastname,r->last);
		strcpy(A.train_name, r->train);
		strcpy( A.departuretime, r->dtime);
		strcpy(A.from, r->from);
		strcpy(A.to, r->to);
		A.fare = r->fare;
		A.pnrno = r->pnrno;
		A.dd = P->dd;
		A.mm = P->mm;
		A.yy = P->yy;
		A.no_of_ticket = r->ticket;
		A.trainno1 = r->tno;
		fwrite(&A, sizeof(ticket), 1, fp);
		r = r->next;
	}
	if(r->next == NULL) {
		strcpy(A.firstname, r->name);
		strcpy(A.lastname,r->last);
		strcpy(A.train_name, r->train);
		strcpy(A.arrivaltime, r->atime);
		strcpy( A.departuretime, r->dtime);
		strcpy(A.from, r->from);
		strcpy(A.to, r->to);
		A.fare = r->fare;
		A.pnrno = r->pnrno;
		A.dd = P->dd;
		A.mm = P->mm;
		A.yy = P->yy;
		A.no_of_ticket = r->ticket;
		A.trainno1 = r->tno;
		fwrite(&A, sizeof(ticket), 1, fp);
	}
	fclose(fp);
	return copy;
}
