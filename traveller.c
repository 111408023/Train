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
#include "login.h"
#include "traveller.h"
#include "newtraveller.h"
#include "seat.h"
#include "reserved.h"
#include "support.h"
int d = 0, m = 0, a = 0, g, qf;
int *x, *y;
float b;
char date[15];
available w;
train help[15];
void journeyplanner(char *, char *, int, int, int);
fake check_date(int, int, int);
ticket cancellation(int, char *, char *);
available chech_ticket(int, int);
ticket book_ticket(int, float, char *, char *, int, int, int);
ticket form(int, int, float, char *, char *, int, int, int);
ticket refund(int);
void printticket(ticket, float);
float fare(int, int);
info enquiries(int, char *, int, int , int);
void printmenu2() {
	printf("Choose a option\n");
	printf("1. journey planner\n");
	printf("2. cancel ticket\n");
	printf("3. refunds\n");
	printf("4. enquiries\n");
	printf("5. exit\n");
}
void travellerlogin() {
	//newtraveller K;
	int i, pnr, yeah, trainno, dd ,mm ,yy;
	char j[10], k[10], trainname[20];
	ticket daya, found; 
	traveller M;
	newtraveller S;
	fake date;
	info get;
	char from[15], to[15], name[15], last[15];
	FILE *fp;
	FILE *fp1;
	fp = fopen("login2.txt", "rb");
	fp1 = fopen("newaccount.txt", "rb");
	printf("enter your username and password\n");
	scanf("%s%s", j, k);
	fread(&S, sizeof(newtraveller), 1, fp1);
	while(fread(&M, sizeof(traveller), 1, fp) == 1) {
		if((strcmp(M.username,j)== 0) && (strcmp(M.password,k)== 0)) {
			d = 1;
		}
	}
	if(d == 1) {
		while(1) {
			printmenu2();
			scanf("%d", &i);
		
		switch(i) {
			case 1:
				printf(" From Station\n");
				scanf(" %s", from);
				printf(" To Station\n");
				scanf(" %s", to);
				printf("Enter journey date :-\n DD MM YY\n");
				scanf("%d %d %d", &dd, &mm, &yy);
				date = check_date(dd, mm, yy);
				journeyplanner(from, to, dd, mm, yy);
				break;
			case 2:
				printf("Enter your pnrno\n");
				scanf("%d", &pnr);
				printf("Enter your first name and last name\n");
				scanf("%s %s", name, last);
				daya = cancellation(pnr, name, last);
				
				if(daya.pnrno == pnr) {
					printf("****************************************************\n");
					printf("You are welcome %s %s\n", daya.firstname, daya.lastname);
					printf("you have successfully cancelled your reservation\n");
					printf("Your money will be refunded soon\n");
					printf("FOR REFUND PLEASE GO TO OUR REFUND MENU\n");
					printf("****************************************************\n\n");
					break;
				
				}
				else
					printf("Dear customer you have not reserved your seat\n");
				 break; 
				//It will delete the entry from file and increase the availability by 1 
			case 3:
				printf("Enter your pnr no\n");
				scanf("%d", &pnr);
				found = refund(pnr);
				if(found.pnrno == pnr) {
					printf("*************************************************\n");
					printf("DEAR %s %s\n", found.firstname, found.lastname);
					printf(" YOUR ACCOUNT HAS BEEN CREDITED BY RS :- %f\n", found.fare);
					printf("*************************************************\n");
				}
				else
					printf("DEAR COSTUMER YOU HAVE NOT CANCELLED YOUR TICKET YET\n");
				break;
			case 4:
				printf("Enter the train no and train name\n");
				scanf("%d %s", &trainno, trainname);
				printf("Enter the date\nDD MM YY\n");
				scanf("%d %d %d",&dd, &mm, &yy);
				date = check_date(dd, mm, yy);
				get = enquiries(trainno, trainname, dd, mm, yy);
				if((get.dd == dd) && (get.mm == mm) && (get.yy == yy)) {
					printf("*****************************\n");
					printf("%d  ", get.trainno);
					printf("%s\t", get.train_name);
					printf("%s  ", get.notice);
					printf(" BY %d MINS\n", get.time);
					printf("*****************************\n");
	
				}
				else
					printf("NO NOTICE AVAILABLE\n");	

				//just prints the notices from admin
				break;
			case 5:
				main();
		}
		}

	}
	else 
		printf("Username or password is wrong\n");
}
void signup() {
	char from[15], to[15];
	newtraveller K;
	FILE *fp;
	FILE *fp1;	
	int i, dd, mm, yy;
	traveller S;
	fp = fopen("newaccount.txt", "ab+");
	fp1 = fopen("login2.txt", "ab+");
	printf("enter your first name, last name and gender\n");
	scanf(" %s %s %c", K.firstname, K.lastname, &K.gender);
	printf("enter your aadhar card no, email and mobile no\n");
	scanf(" %s %s %s", K.aadharno, K.email, K.mobile);
	printf("enter nationality, state, city\n");
	scanf(" %s %s %s", K.nationality, K.state, K.city);
	printf("enter your address line 1 and address line 2\n");
	scanf(" %s %s", K.addressline1, K.addressline2);
	printf("set username and password\n");
	printf("Caution : username and password should not be more than 10 characters\n");
	scanf(" %s %s", K.username, K.password);
	strcpy(S.username, K.username);
	strcpy(S.password, K.password);
	fwrite(&K, sizeof(traveller), 1, fp);
	fwrite(&S, sizeof(traveller), 1, fp1); 
	printf("*********************************************\n");
	printf("congrats %s %s your account has been created\n", K.firstname, K.lastname);
	printf("FOR SIGN IN GO TO SIGN IN OPTION\n");
	printf("*********************************************\n");
}
void journeyplanner(char *f, char *t, int dd, int mm, int yy) {
				int i = 0, k = 0, s = 0, z = 0, v, e = 0, yo = 0, q, choice;
				ticket u;
				float charge, trip;
				reserved end;
				fake date;
				char from[15], to[15];
				FILE *fd;
				fd = fopen("coep.txt", "r");
		
while(fscanf(fd,"%d %s %s %d %s %d %s %d %s %d %s %s %s %d", &help[i].trainno, help[i].trainname, help[i].station1, &help[i].dis1, help[i].station2, &help[i].dis2, help[i].station3, &help[i].dis3, help[i].station4, &help[i].dis4, help[i].station5, help[i].arrival, help[i].departure, &help[i].totaltime) != EOF) {
	i++;			
		}
	// we have to declare *x, *y and m globally since we can calculate distace of particular train from that
			printf("************************************\n");
				int n = 0, oh, rs;
				x = (int *)malloc(18*sizeof(int));
				y = (int *)malloc(18*sizeof(int));
				for(n = 0; n < i; n++) {
					k = 0;
					if((strcmp(f, help[n].station1) == 0)) {
						k = 1; // we can use stack here
					}
					if(k == 1) {
						if((strcmp(t, help[n].station2) == 0)) {
							x[m++] = n;
							z = 1;
							a = a + help[n].dis1;
						}
						else if((strcmp(t, help[n].station3) == 0)) {
							x[m++] = n;
							y[e++] = 3;
							z = 1;
							a = a + help[n].dis1 + help[n].dis2;
						}
						else if((strcmp(t, help[n].station4) == 0)) {
							x[m++] = n;
							y[e++] = 4;
							z = 1;
							a = a + help[n].dis1 + help[n].dis2 + help[n].dis3;
						}
						else if((strcmp(t, help[n].station5) == 0)) {
							x[m++] = n;
							y[e++] = 5;
							z = 1;
							a = a + help[n].dis1 + help[n].dis2 + help[n].dis3 + help[n].dis4;
						}
					}
					if((k == 1) && (z == 1)) {
						g = distance(a);
						printf("%d %s %s %s %s\n", help[n].trainno, help[n].trainname, help[n].type, help[n].arrival, help[n].departure);
						printf("Total Distance = %d\n", g);	
						printf("*************************************\n");
								z = 0;
								k = 0;
								a = 0;
								s = 1;			
	
						}
							
				//}
				if(k == 0) {
					//for(n = 0; n < i; n++) {
						if((strcmp(f, help[n].station2) == 0)) {
							k = 1;
							y[e++] = 2;
						}
						if(k == 1) {
							if((strcmp(t, help[n].station3) == 0)) {
								x[m++] = n;
								y[e++] = 3;
								z = 1;
								a = a + help[n].dis2;
			
							}
							else if((strcmp(t, help[n].station4) == 0)) {
								x[m++] = n;
								y[e++] = 4;
								z = 1;
								a = a + help[n].dis2 + help[n].dis3;
							}
							else if((strcmp(t, help[n].station5) == 0)) {
								x[m++] = n;
								y[e++] = 5;
								z = 1;
								a = a + help[n].dis2 + help[n].dis3 + help[n].dis4;
							}
						}
						if((k == 1) && (z == 1)) {
							g = distance(a);
							printf("%d %s %s %s %s\n", help[n].trainno, help[n].trainname, help[n].type, help[n].arrival, help[n].departure);		
							printf("Total Distance = %d\n", g);
							printf("****************************************\n");
							z = 0;
							k = 0;
							a = 0;
							s = 1;
						}
					
					//}
				}
								
				 if(k == 0) {
					//for(n = 0; n < i; n++) {
						if((strcmp(f, help[n].station3) == 0)) {
							k = 1;
							y[e++] = 3;
						}
						if(k == 1) {
							if((strcmp(t, help[n].station4) == 0)) {
								x[m++] = n;
								y[e++] = 4;
								z = 1;
								a = a + help[n].dis3;
							}
							else if((strcmp(t, help[n].station5) == 0)) {
								x[m++] = n;
								y[e++] = 5;
								z = 1;
								a = a + help[n].dis3 + help[n].dis4;
							}
						
						}
						if((k == 1) && (z == 1)) {
							g = distance(a);
							printf("%d %s %s %s %s\n", help[n].trainno, help[n].trainname, help[n].type, help[n].arrival, help[n].departure);	
							printf("Total Distance = %d\n", g);
							printf("*************************************\n");
								z = 0;
								k = 0;
								a = 0;
								s = 1;
						}
			
					//}
				}					
				if(k == 0) {
					//for(n = 0; n < i; n++) {
						if((strcmp(f, help[n].station4) == 0)) {
							k = 1;
							y[e++] = 4;
						if(k == 1) {
							if((strcmp(t, help[n].station5) == 0)) {
								x[m++] = n;
								y[e++] = 5;
								z = 1;
								a = a + help[n].dis4;
								
							}
						}
						if((k == 1) && (z == 1)) {
							g = distance(a);
							
							printf("%d %s %s %s %s\n", help[n].trainno, help[n].trainname, help[n].type, help[n].arrival, help[n].departure);		
							printf("Total Distance = %d\n", g);
							printf("*************************************\n");
							z = 0;
							k = 0;
							a = 0;
							s = 1;
						}
					
					//}
				}
			}
		}
				if(s == 0) { 
					printf("No Trains available\n");
					printf("Want to continue\n");
					printf("1. Yes 2. No\n");
					scanf("%d", &choice);
					switch(choice) {
						case 1:
							printf(" From Station and To Station :-\n");
							scanf(" %s %s", from, to);
							printf("Enter journey date :-\n");
							scanf("%d %d %d", &dd, &mm, &yy);
							date = check_date(dd,  mm, yy);
							journeyplanner(from, to, dd, mm, yy);
							break;
						case 2:
							break;
					}
				}
			else {		
				printf("want to book tickets?\n");
				printf("1. Yes 2. No\n");
				scanf("%d", &v);
				
			}
			switch(v) {
				case 1:
					printf("Enter the train no\n");
					scanf("%d", &q);
					while(yo < m) {
						if(help[x[yo]].trainno == q) {
							w = chech_ticket(q, x[yo]);
							printf("Available Ticket = %d\n", w.total_ticket); 
							charge = fare(1, g);
							printf("Fare for one ticket = %f\n", charge); 
							u = book_ticket(q, charge, f, t, dd, mm, yy);
							rs = u.no_of_ticket;
							trip = u.fare;
							printticket(u, trip);
							break;
						}
					yo++;
					}
				case 2:
					break;
			}
			
	
}

int distance(int a) {
	return a;
}
available chech_ticket(int q, int win) {
	char from[15], to[15];
	FILE *fh, *fd, *fp;
	available A, B[15], lag;
	ticket M;
	node *p, temp;
	list *l;
	int i = 0, k = 0, count = 0, n = 0, a = 0, t = 0, u, dd, mm, yy;
	l = (list *)malloc(sizeof(list));
	p = (node *) malloc(sizeof(node));
	fh = fopen("available.txt", "r");
	fd = fopen("ticket2.txt", "ab+");
	while(fread(&A, sizeof(available), 1, fh) == 1) {
		B[i].total_ticket = A.total_ticket; 
		B[i].upper = A.upper;
		B[i].middle = A.middle;
		B[i].lower = A.lower;
		B[i].waiting = A.waiting;
		i++;
	}
	while(fread(&M, sizeof(ticket), 1, fd) == 1) {
		if(M.trainno1 == q) {
			count++;
		}
	}

	while(n < i) {
		if(n == win) {
			if(B[n].waiting > 50) {
				printf("REGRET :- NO MORE TICKETS AVAILABLE\n");
				printf("Do you want to continue\n");
				printf("1. Yes 2. No\n");
				scanf("%d", &u);
				switch(u) {
					case 1:
						printf(" From Station and To Station :-\n");
						scanf(" %s %s", from, to);
						printf("Enter journey date :-\nDD MM YY\n");
						scanf("%d %d %d", &dd, &mm, &yy);
						journeyplanner(from, to, dd, mm, yy);
						break;
					case 2:
						break;
				}
			}
			else if(B[n].total_ticket < 0)
				B[n].waiting++;
			else
				B[n].total_ticket = B[n].total_ticket - count;
		}
		// use of linked list for the backup of data in file for changing it 
		if(n == 0) {
			l->head = NULL;
			l->tail = NULL;
		}
			p->ticketav = B[n].total_ticket;
			p->ticketup = B[n].upper;
			p->ticketmi = B[n].middle;
			p->ticketlo = B[n].lower;
			p->ticketwa = B[n].waiting;
			if(l->head == NULL) {
				l->head = p;
				l->tail = p;
				p->next = NULL;
				p->prev = NULL;
			}
			else {
				p->prev = l->tail;
				p->next = NULL;
				l->tail->next = p;
				l->tail = l->tail->next;
			}
		n++;
	}
	lag = B[win];
	fclose(fh);
	fclose(fd);	 		
	return lag;
}
ticket book_ticket(int q, float charge, char *from, char *to, int dd, int mm, int yy) {
	int z, h, a, b, c;
	char f[15], t[15];
	float fare;
	fare = charge;
	ticket good;
	printf(" How many tickets you want to book?\n");
	scanf("%d", &h);
	strcpy(f, from);
	strcpy(t, to);
	a = dd;
	b = mm;
	c = yy;
	//z = pnr_generator(h)
	good = form(h, q, fare, f, t, a, b, c);
	return (good);
}
ticket form(int h, int q, float charge, char *from, char *to, int dd, int mm, int yy) {
	int i = 0, count = 0, kim, sbi = 0, my;
	char id[15], pass[15];
	FILE *fd, *fh, *fp, *era;
	traveller P;
	reserved pos;
	ticket w, copy, l;
	fp = fopen("ticket2.txt", "ab+");
	fd = fopen("coep.txt", "r");
	fh = fopen("login2.txt", "rb+");
	era = fopen("reserved.txt", "ab+");
	for(kim = 0; kim < h; kim++) {
		printf("enter %dst traveller's first name, last name\n", kim + 1);
		scanf(" %s %s", w.firstname, w.lastname);
	
	
		while(fscanf(fd,"%d %s %s %d %s %d %s %d %s %d %s %s %s %d", &help[i].trainno, help[i].trainname, help[i].station1, &help[i].dis1, help[i].station2, &help[i].dis2, help[i].station3, &help[i].dis3, help[i].station4, &help[i].dis4, help[i].station5, help[i].arrival, help[i].departure, &help[i].totaltime) != EOF) {
			if(help[i].trainno == q) {
				strcpy(w.train_name, help[i].trainname);
				strcpy(w.arrivaltime, help[i].arrival);
				strcpy(w.departuretime, help[i].departure);
				
			}
			i++;
		}
		my = pnr(h, kim);
		strcpy(w.from, from);
		strcpy(w.to, to);
		w.pnrno	= my;			
		w.trainno1 = q;
		w.no_of_ticket = h;
		w.fare = charge;
		w.dd = dd;
		w.mm = mm;
		w.yy = yy;
		copy = w;
		fwrite(&w, sizeof(ticket), 1, fp);
		
	}
		printf("Enter SBI account no:\nIT IS SAME AS USERNAME\n");
		scanf("%s", id);
		printf("Enter Password: \nIT IS SAME AS PASSWORD\n");
		scanf("%s", pass);
		while(fread(&P, sizeof(traveller), 1, fh) == 1) {
			if((strcmp(P.username, id) == 0) && (strcmp(P.password, pass) == 0)) {
				sbi = 1;
				strcpy(pos.firstname, copy.firstname);
				strcpy(pos.lastname, copy.lastname);
				fwrite(&pos, sizeof(reserved), 1, era);
				break; 
			}
					
		}
	fclose(fd);
	fclose(fp);
	fclose(fh);
	fclose(era);
	if(sbi == 1) 
			return (copy);
	else
		printf("SBI ACCOUNT NO OR PASSWORD IS WRONG\n");
}
int pnr(int h, int kim) {
	FILE *f, *fp;
	ticket l, work;
	int pnrno, count = 0, temp = 0;
	f = fopen("ticket2.txt", "ab+");
	fp = fopen("cancelled.txt", "ab+");
	while(fread(&work, sizeof(ticket), 1, fp) == 1) {
		temp++;
	}
		while(fread(&l, sizeof(ticket), 1, f) == 1) {
				count++;
			}
			if(h > 1) {
				pnrno = 102345 + count + kim + temp;
				printf("YOUR PNR NO IS:- %d\n", pnrno);  
			}
			else if(h == 1) {		
				pnrno = 102345 + count + temp;
				printf("YOUR PNR NO IS:- %d\n", pnrno);
			}
	fclose(f);
	fclose(fp);
	return pnrno;
	}
float fare(int h, int distance) {
	return h*0.64*distance;
}	
void printticket(ticket u, float trip) {
	float k;
	printf("*******************************************************************\n");
	printf("				Date:- %d-%d-%d\n", u.dd, u.mm, u.yy);
	printf("          			PNR NO :- %d\n", u.pnrno);
	printf("Name :- %s %s\n", u.firstname, u.lastname);
	printf(" From :- %s	To :- %s\n", u.from, u.to); 
	printf("Train no :- %d Train name:- %s\n Arrival :-%s Departure :- %s No of seats :-%d\n", u.trainno1, u.train_name, u.arrivaltime, u.departuretime, u.no_of_ticket);
	k = u.fare * u.no_of_ticket;
	printf("FARE = %f\n", k);
	printf("*******************************************************************\n");
}

