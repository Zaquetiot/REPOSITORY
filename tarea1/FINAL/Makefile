all: split.o funciones.o main.o compile clear

split.o:
	gcc -c split.c -Wall
funciones.o:
	gcc -c funciones.c -Wall
main.o:
	gcc -c main.c -Wall
compile:
	gcc split.o funciones.o main.o -o tarea1
clear:
	rm -f *.o
