#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "login.h"
#include "traveller.h"
#include "newtraveller.h"
int d = 0, m = 0, a = 0, g;
int *x, *y;
float b;
void journeyplanner();
float fare(int);
void printmenu2() {
	printf("Choose a option\n");
	printf("1. journey planner\n");
	printf("2. cancel ticket\n");
	printf("3. refunds\n");
	printf("4. enquiries\n");
}
void travellerlogin() {
	//newtraveller K;
	int i;
	char j[10], k[10];
	traveller M;
	newtraveller S;
	FILE *fp;
	FILE *fp1;
	fp = fopen("login2.txt", "rb");
	fp1 = fopen("newaccount.txt", "rb");
	printf("enter your username and password\n");
	scanf("%s%s", j, k);
	fread(&M, sizeof(traveller), 1, fp);
	fread(&S, sizeof(newtraveller), 1, fp1);
	if((strcmp(M.username,j)== 0) && (strcmp(M.password,k)== 0)) {
		d = 1;
	}
	if(d == 1) {
		printmenu2();
		scanf("%d", &i);
		switch(i) {
			case 1:
				journeyplanner();
				break;
			case 2:
				//cancellation();
				break;
			case 3:
				//refund();
				break;
			case 4:
				//enquiries();
				break;
		}

	}
}
void signup() {
	newtraveller K;
	FILE *fp;
	FILE *fp1;	
	int i;
	traveller S;
	fp = fopen("newaccount.txt", "ab+");
	fp1 = fopen("login2.txt", "ab+");
	printf("enter your first name, last name and gender\n");
	scanf(" %s %s %c", K.firstname, K.lastname, &K.gender);
	printf("Enter your DOB and occupation\n");
	scanf(" %s %s", K.DOB, K.occupation);
	printf("enter your aadhar card no, email and mobile no\n");
	scanf(" %s %s %s", K.aadharno, K.email, K.mobile);
	printf("enter nationality, state, city\n");
	scanf(" %s %s %s", K.nationality, K.state, K.city);
	printf("enter your address line 1 and address line 2\n");
	scanf(" %s %s", K.addressline1, K.addressline2);
	printf("set username and password\n");
	printf("Caution : username and password should not be more than 10 characters\n");
	scanf(" %s %s", K.username, K.password);
	fwrite(&K, sizeof(traveller), 1, fp);
	strcpy(S.username, K.username);
	strcpy(S.password, K.password);
	fwrite(&S, sizeof(traveller), 1, fp1); 
	printf("congrats ypor account has been created\n");
	printf("Do you want to sign in into your account\n");
	printf("1. Yes 2. No\n");
	scanf("%d", &i);	 
	switch(i) {
		case 1 :
			travellerlogin();
		
		case 2 :
			break;
		default:
			break;
	}

}
void journeyplanner() {
				
				train help[15];
				int i = 0, k = 0, s = 0, z = 0, n=0, v, e = 0;
				
				char f[15];
				char t[15];
				FILE *fd;
				fd = fopen("coep.txt", "r");
				printf(" From Station and To Station :-\n");
				scanf(" %s%s", f, t);
				
while(fscanf(fd,"%d %s %s %d %s %d %s %d %s %d %s %s %s %d", &help[i].trainno, help[i].trainname, help[i].station1, &help[i].dis1, help[i].station2, &help[i].dis2, help[i].station3, &help[i].dis3, help[i].station4, &help[i].dis4, help[i].station5, help[i].arrival, help[i].departure, &help[i].totaltime) != EOF) {
	i++;			
		}	

	// we have to declare *x, *y and m globally since we can calculate distace of particular train from that
			printf("*****************\n");

				x = (int *)malloc(18*sizeof(int));
				y = (int *)malloc(18*sizeof(int));
				for(n = 0; n < i; n++) {
					if((strcmp(f, help[n].station1) == 0)) {
						k = 1; // we can use stack here
						y[e++] = 1;
					}
					if(k == 1) {
						if((strcmp(t, help[n].station2) == 0)) {
							x[m++] = n;
							y[e++] = 2;
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
						b = fare(g);
						printf("%d %s %s %s %s\n", help[n].trainno, help[n].trainname, help[n].type, help[n].arrival, help[n].departure);
						printf("Total Distance = %d\n", g);	
						printf("Total Fare = %f\n", b);	
						}
					z = 0;
					k = 0;
					a = 0;
					s = 1;			
					
				}
				if(k == 0) {
					for(n = 0; n < i; n++) {
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
							b = fare(g);
							printf("%d %s %s %s %s\n", help[n].trainno, help[n].trainname, help[n].type, help[n].arrival, help[n].departure);		
							printf("Total Distance = %d\n", g);
							printf("Total Fare = %f\n", b);
						}
					z = 0;
					k = 0;
					a = 0;
					s = 1;
					}
				}
					
				 if(k == 0) {
					for(n = 0; n < i; n++) {
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
							b = fare(g);
							printf("%d %s %s %s %s\n", help[n].trainno, help[n].trainname, help[n].type, help[n].arrival, help[n].departure);	
							printf("Total Distance = %d\n", g);
							printf("Total Fare = %f\n", b);	
						}
					z = 0;
					k = 0;
					a = 0;
					s = 1;
					}
				}					
				if(k == 0) {
					for(n = 0; n < i; n++) {
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
							b = fare(g);
							printf("%d %s %s %s %s\n", help[n].trainno, help[n].trainname, help[n].type, help[n].arrival, help[n].departure);		
							printf("Total Distance = %d\n", g);
							printf("Total Fare = %f\n", b);
						}
					z = 0;
					k = 0;
					a = 0;
					s = 1;
					}
				}
			
				if(s == 0) 
					printf("No Trains available");
			printf("want to continue?\n");
			printf("1. Yes 2. No\n");
			scanf("%d", &v);
			switch(v) {
				case 1:
					journeyplanner();
					break;
				case 2:
					break;
			}
			
	}
}

int distance(int a) {
	return a;
}
float fare(int g) {
	return 0.63 * g;
}
