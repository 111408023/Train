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
#include "support.h"
fake check_date(int, int , int);
info enquiries(int, char *, int, int, int);
void init1(list1 *l) {
	l->head = NULL;
	l->tail = NULL;
}
list1 *l;
void notice(int trainno, char *trainname, int dd, int mm, int yy) {
	// ask the admin for the date it should not be greater than tommorow date
	info get;
	FILE *fp;	
	fp = fopen("notice.txt", "ab+");
	get.trainno = trainno;
	strcpy(get.train_name, trainname);
	printf("ENTER NOTICE eg:- LATE OR EARLY\n");
	scanf("%s", get.notice);
	get.dd = dd;
	get.mm = mm;
	get.yy = yy;
	printf("ENTER TIME IN MINS\n");
	scanf("%d", &get.time);
	fwrite(&get, sizeof(info), 1, fp);
	printf("NOTICE HAS BEEN RECORDED, SIR\n");
	fclose(fp);
}
info enquiries(int trainno, char *trainname, int dd, int mm, int yy) {
	// in the while loop first it will check date then it will print the notice on that date
	info read;
	FILE *fp;
	int count = 0;
	printf("%s\n", trainname);
	fp = fopen("notice.txt", "rb+");
	if(fp == NULL)
		return;
	while(fread(&read, sizeof(info), 1, fp) == 1) {
		if(read.trainno == trainno) {
			if((strcmp(read.train_name, trainname) == 0)) {
				if((read.dd == dd) && (read.mm == mm) && (read.yy == yy)) {
					fclose(fp);
					return read;
				}
			}
		}
	count++;
	}
	fclose(fp);
}
fake check_date(int dd, int mm, int yy) {
	fake date;
	
	if((yy < 15) || (yy > 17)) {
		printf("**********\n"); 
		printf("INVALID DATE\n");
		main();
	}
	if((mm < 1) || (mm > 12)) {
		printf("INVALID DATE\n");
		main();
	}
	if((dd < 1) || (dd > 31)) {
		printf("INVALID DATE\n");
		main();	
	}
	if((yy % 4 == 0) && (mm == 2) && (dd > 29)) {
		printf("INVALID DATE\n");
		main();
	}
	if((yy % 4 != 0) && (mm == 2) && (dd > 28)) {
		printf("INVALID DATE\n");
		main();
	}
	if((mm % 2 == 0) && (dd > 30)) {
		printf("INVALID DATE\n");
		main();
	}
	if((yy == 15) || (yy == 16)) {
		date.dd = dd;
		date.mm = mm;
		date.yy = yy;
		return date;
	}
	
}
