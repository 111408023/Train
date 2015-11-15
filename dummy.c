#include<stdio.h>
#include "traveller.h"
#include "login.h"
#include "seat.h"
#include "support.h"
int main(int argc, char *argv[]) {
	int count = 0;
	ticket w;
	FILE *fp;
	fp = fopen(argv[1], "rb+");
	//while(i < 10) {
	//	scanf("%d %d %d %d %d", &w.total_ticket, &w.upper, &w.middle, &w.lower, &w.waiting);
	//	fwrite(&w, sizeof(w), 1, fp);
	//	i++;
	//}
		while(fread(&w, sizeof(ticket), 1, fp) == 1) { 
		printf("%s %s %d %d %d %f %s %s %s %d %d %d %s %s\n", w.firstname, w.lastname, w.pnrno, w.trainno1, w.no_of_ticket, w.fare, w.train_name, w.from, w.to, w.dd, w.mm, w.yy, w.arrivaltime, w.departuretime);
		count++;
		}
		//printf("%d\n", count);
	/*while(fread(&w, sizeof(info), 1, fp) == 1) 
		printf("%d %s %s %d %d %d\n", w.trainno, w.train_name, w.notice, w.dd, w.mm, w.yy); 
	fclose(fp);*/
	return 0;
}
