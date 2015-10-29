#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "traveller.h"
void signup();
void travellerlogin();
void printmenu() {
	printf("Enter your choice\n");
	printf("1. admin login\n");
	printf("2. traveller login\n");
	printf("3. Sign up\n");
	printf("4. Alerts and updates\n");
	printf("5. PNR status\n");
}
int main() {
	int i;
	printmenu();	
	scanf("%d", &i);
	switch(i) {
		case 1 :
			adminlogin();
			break;
		case 2 :
			travellerlogin();
			break;
		case 3 :
			signup();
			break;
		case 4 :
			//alerts(arguments from admin function)
			break;
		case 5 :
			//pnrstatus(int pnrno);
			break;
	}
}
