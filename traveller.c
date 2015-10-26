#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "login.h"
#include "newtraveller.h"
void travellerlogin() {
	//newtraveller K;
	int d;
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
		printf("%s\n%s\n", M.username, M.password);
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
	}
}
