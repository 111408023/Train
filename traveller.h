#include<stdio.h>
#include<string.h>

/*typedef struct station {
	char station_name[20];
	struct station **ptr;
	int *dis;
}station;
station *arr[50];*/
typedef struct train {
	int trainno;
	char trainname[25];
	char type[10];
	char station1[15];
	int dis1;
	char station2[15];
	int dis2;
	char station3[15];
	int dis3;
	char station4[15];
	int dis4;
	char station5[15];
	
	char arrival[10];
	char departure[10];
	int totaltime;
}train;

typedef struct ticket {
	char firstname[18];
	char lastname[18];
	int pnrno;
	int trainno1;
	char date[12];
	char arrivaltime[10];
	char departuretime[10];
	int time;
	
}ticket;


