#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "login.h"
void adminlogin() {
	int i;
	int d;
	char u[10], p[10];
	admin G;
	FILE *fp;
	fp = fopen("login1.txt", "rb");
	printf("enter your username, password and id.no.\n");
	scanf("%s%s%d", u, p, &i);
	fread(&G, sizeof(admin), 1, fp);
	if((strcmp(G.username,u)== 0) && (strcmp(G.password,p)== 0) && i==G.idno) {
		d = 1;
		//printf("%s\n%s\n%d\n", G.username, G.password, G.idno);
	}
	

	/*if(d = 1) {
		void notice();// display the position of train if it is late or on time
		void reserved();// to see reserved people	
		void vacant();// to display the vacant seats
		void cancelled()// to see people who have cancelled their tickets
		void newtrains() // newly launched trains
	*/
	}

