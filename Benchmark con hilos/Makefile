GCC = gcc 
FLAGS = -std=c99 -pthread
PROGS = posix_01

all: posix_01

posix_01:
	$(GCC) $(FLAGS) $@.c -c 
	$(GCC) $(FLAGS) modulo.c -c
	$(GCC) $(FLAGS) modulo.o $@.o -o $@

clean:
	$(RM) $(PROGS) *.o