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
void signup();
void travellerlogin();
ticket pnr_status(int);
void printmenu() {
	printf("Enter your choice\n");
	printf("1. admin login\n");
	printf("2. traveller login\n");
	printf("3. Sign up\n");
	printf("4. PNR INFO\n");
	printf("5. Exit\n");
}
int main() {
	int i;
	int pnrno;
	ticket fair;
	printmenu();	
	scanf("%d", &i);
	switch(i) {
		case 1 :
			adminlogin();
			main();
			break;
		case 2 :
			travellerlogin();
			main();
			break;
		case 3 :
			signup();
			main();
			break;
		case 4 :
			printf("Enter your PNR NO:\n");
			scanf("%d", &pnrno);
			fair = pnr_status(pnrno);
			if(fair.pnrno == pnrno) {
				printf("***********************************\n");
				printf("	DATE :-	%d-%d-%d\n", fair.dd, fair.mm, fair.yy);
				printf("NAME :- %s %s\nTRAIN NO :- %d\n", fair.firstname, fair.lastname, fair.trainno1);
				printf("***********************************\n");
			}
			else
				printf("INVALID PNR NO\n");
			main();
			break;
		case 5 :
			exit(0);
	}
}
