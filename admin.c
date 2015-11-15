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
#include<string.h>
#include<stdlib.h>
#include "login.h"
#include "traveller.h"
#include "seat.h"
#include "support.h"
void menu();
void reserved(char *, int, int, int);
void vacant(char *, int, int, int);
void cancelled(char *);
void notice(int, char *, int , int, int);
fake check_date(int, int, int);
train cover[15];
void menu() {
	printf("1. NOTICE\n");
	printf("2. RESERVED PEOPLE\n");
	printf("3. VACANT SEATS\n");
	printf("4. RESERVATION CANCELLED PEOPLE\n");
	printf("5. EXIT\n");
}
void adminlogin() {
	int i, choice;
	int d = 0, dd, mm, yy, trainno;
	char u[10], p[10], train_name[20];
	admin G;
	info get;
	FILE *fp;
	fp = fopen("login1.txt", "rb");
	printf("enter your username, password and id.no.\n");
	scanf("%s%s%d", u, p, &i);
	while(fread(&G, sizeof(admin), 1, fp) == 1) {
		if((strcmp(G.username,u)== 0) && (strcmp(G.password,p)== 0) && i==G.idno) {
			d = 1;
		}
	}
	if(d == 0) {
		printf("USERNAME PASSWORD OR ID NO IS WRONG\n"); 
	}
	if(d == 1) {
		
		fake date;
		
	while(1) {
		menu();
		scanf("%d", &choice);
		switch(choice) {
			case 1:
				printf("Enter train no and train name\n");
				scanf("%d %s", &trainno, train_name);
				printf("Enter the date for notice\n");
				printf("DD MM YY\n");
				scanf("%d %d %d", &dd, &mm, &yy);
				date = check_date(dd, mm, yy);
				notice(trainno, train_name, dd, mm, yy);
				break;
			case 2:
				printf("Enter Train Name :-\n");
				scanf("%s", train_name);
				printf("Enter date\nDD MM YY\n");
				scanf("%d %d %d", &dd, &mm, &yy);
				date = check_date(dd, mm, yy);
				reserved(train_name, dd, mm, yy);// to see reserved people
				break;
			case 3:	
				printf("Enter Train Name :-\n");
				scanf("%s", train_name);
				printf("Enter date\nDD MM YY\n");
				scanf("%d %d %d", &dd, &mm, &yy);
				date = check_date(dd, mm, yy);
				vacant(train_name, dd, mm, yy);// to display the vacant seats
				break;
			case 4:
				printf("Enter Train Name :-\n");
				scanf("%s", train_name);
				cancelled(train_name);// to see people who have cancelled their tickets
				break;
			case 5:
				main();
		}
		}	
	}
}
void reserved(char *name, int dd, int mm, int yy) {
	ticket you;
	int count = 0;
	FILE *fd;
	fd = fopen("ticket2.txt", "rb+");
	printf("THOSE WHO HAVE RESERVATION FOR THIS TRAIN ARE :-\n\n");
	while(fread(&you, sizeof(ticket), 1, fd) == 1) {
		if((you.dd == dd) && (you.mm == mm) && (you.yy == yy)) { 
			if((strcmp(you.train_name, name) == 0)) {
				printf("%s %s\n", you.firstname, you.lastname);
				count++;
			}
		}
	}
	fclose(fd);
	if(count == 0) 
		printf("NO SUCH TRAIN EXIST OR NO ONE IS RESERVED\n\n");
}
void vacant(char *train, int dd, int mm, int yy) {
	int count = 0, i = 0, new, c = 0;
	ticket you;
	available A, B;
	FILE *fd, *fs, *ft;
	fd = fopen("ticket2.txt", "rb+");
	fs = fopen("available.txt", "rb+");
	ft = fopen("coep.txt", "r");
	
	//We can use stack here
	while(fscanf(ft,"%d %s %s %d %s %d %s %d %s %d %s %s %s %d", &cover[i].trainno, cover[i].trainname, cover[i].station1, &cover[i].dis1, cover[i].station2, &cover[i].dis2, cover[i].station3, &cover[i].dis3, cover[i].station4, &cover[i].dis4, cover[i].station5, cover[i].arrival, cover[i].departure, &cover[i].totaltime) != EOF) {
		if((strcmp(cover[i].trainname, train) == 0)) {
			new = i;
			//printf("%d\n", new);
			break;
		}
		i++;			
	}
	while(fread(&you, sizeof(ticket), 1, fd) == 1) {
		if((you.dd == dd) && (you.mm == mm) && (you.yy == yy)) {
			if((strcmp(you.train_name, train) == 0)) {
				count++;
			}
		}
	}
	if(count == 0) { 
		printf("NO SUCH TRAIN EXIST\n\n");
		return;
	}
	while(fread(&A, sizeof(available), 1, fs) == 1) {
		if(c == new) {
			B.total_ticket = A.total_ticket - count; 
			B.upper = A.upper;
			B.middle = A.middle;
			B.lower = A.lower;
			B.waiting = A.waiting;
			if(B.waiting > 50) 
				printf("REGRET\n");
			else if(B.total_ticket < 0)
				printf("NO VACANT SEATS\n");
			else if(B.total_ticket > 0) 
				printf(" VACANT SEATS = %d\n", B.total_ticket);
		break;
		}
		c++;
	}
fclose(fd);
fclose(fs);
fclose(ft);
	
}
// In this Function We can use queue
void cancelled(char *train) {
	ticket C;
	int count = 0;
	FILE *fp;
	fp = fopen("cancelled.txt", "rb+");
	while(fread(&C, sizeof(ticket), 1, fp) == 1) {
		if((strcmp(C.train_name, train) == 0)) {
			printf("%s %s\n", C.firstname, C.lastname);
			count++;
		}
	}
	fclose(fp);
	if(count == 0)
		printf("NO SUCH TRAIN EXIST\n\n");
}
