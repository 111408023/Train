project: main.o admin.o traveller.o gau.o support.o 
	gcc main.o admin.o traveller.o gau.o support.o -o project

main.o:main.c
	gcc -c main.c 
admin.o:admin.c
	gcc -c admin.c
traveller.o:traveller.c 
	gcc -c traveller.c 
gau.o:gau.c
	gcc -c gau.c
support.o:support.c
	gcc -c support.c

