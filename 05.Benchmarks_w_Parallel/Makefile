GCC = gcc-11
FLAGS = -pedantic -Wall
CFLAGS = -fopenmp -lpthread 
PROGS= MM1c MM1f MMPosix MM1cOMP MM1fOMP

PROGS: MM1c MM1f MMPosix MM1cOMP MM1fOMP

MM1c:
	$(GCC) $(FLAGS) modulo.c -c 
	$(GCC) $(FLAGS) $@.c -c 
	$(GCC) $(FLAGS) modulo.o $@.o -o $@
	
MM1f:
	$(GCC) $(FLAGS) modulo.c -c 
	$(GCC) $(FLAGS) $@.c -c 
	$(GCC) $(FLAGS) modulo.o $@.o -o $@
		
MMPosix:
	$(GCC) $(FLAGS) modulo.c -c $(CFLAGS)
	$(GCC) $(FLAGS) $@.c -c $(CFLAGS) 
	$(GCC) $(FLAGS) modulo.o $@.o -o $@ $(CFLAGS) 

MM1cOMP:
	$(GCC) $(FLAGS) modulo.c -c $(CFLAGS) 
	$(GCC) $(FLAGS) $@.c -c $(CFLAGS) 
	$(GCC) $(FLAGS) modulo.o $@.o -o $@ $(CFLAGS) 
 
MM1fOMP:
	$(GCC) $(FLAGS) modulo.c -c $(CFLAGS) 
	$(GCC) $(FLAGS) $@.c -c $(CFLAGS) 
	$(GCC) $(FLAGS) modulo.o $@.o -o $@ $(CFLAGS) 

clean:
	$(RM) $(PROGS) *.o
