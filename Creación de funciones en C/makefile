GCC = gcc
FLAGS = -ansi -pedantic -Wall
PROGS = main

main:
	$(GCC) $(FLAGS) funciones.c -c
	$(GCC) $(FLAGS) main.c -c
	$(GCC) $(FLAGS) -o main funciones.o main.o 

clean:
	$(RM) $(PROGS) *.o

