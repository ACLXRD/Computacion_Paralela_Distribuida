GCC = gcc 
FLAGS = -pedantic -Wall
CFLAGS = -lm -pthreads

PROGS: MM1c MM1f


MM1c:
	$(GCC) $(FLAGS) modulo.c -c
	$(GCC) $(FLAGS) $@.c -c 
	$(GCC) $(FLAGS) modulo.o $@.o -o $@
	
MM1f:
	$(GCC) $(FLAGS) modulo.c -c
	$(GCC) $(FLAGS) $@.c -c 
	$(GCC) $(FLAGS) modulo.o $@.o -o $@

clean:
	$(RM) $(PROGS) *.o
