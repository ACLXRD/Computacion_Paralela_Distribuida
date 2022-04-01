/*Fecha: 15/03/2022
* Autor: Andres C. Lopez R.
* Subject: Parallel and Distributed Computing.
* Topic: Poxis implemetation (Library)
* Description: Application for matrix multiplication
  with the classical algorithm (rows x columns) using
  global variables. Also, using the following functions:
    1. Creation of double pointer variables for matrices
    2. Memory reserve for double pointer matrices
    3. Init matrix
    4. Function for the matrix's product:
        4.1.1 The matrix A is divide and those portions 
        will be sent to an individual thread
        4.1.2 The matrix's size will be sent on the 
        execution.
    5. Matrix's size always squared (NxN)
    6. Print matrix with double pointer.
*/

/*Interfaces*/
#include "modulo.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <omp.h>

/** 
* @brief main(): Main function
*/
int main(int argc, char* argv[]){
    if (argc != 3){
        printf("./MMPosix <matrix size> <# of threads>\n");
        return -1;
    }

    /*Init of varaibles for the struct*/
    int N          		= atof(argv[1]);    /* Matrix's size.*/
    int Nthreads   		= atof(argv[2]);    /* Number of threads.*/
    pthread_t *threads 	= (pthread_t*)malloc(N*sizeof(pthread_t)); /*Thread reservation*/
    
     /*Validation f number of cores on PC against the number ent throw parameters*/
    if (Nthreads > omp_get_max_threads( )){
        printf("\nEl numero de hilos debe ser <= que %d\n\n", omp_get_max_threads( ));
        return -1;
    }


	/*Memory creation and reserce for each matrix*/
    double **Ma = memReserve(N); 
    double **Mb = memReserve(N);
    double **Mc = memReserve(N);
    initMatrix_DoublePointers(Ma, Mb, Mc, N);
    
    /*Init of pointer type struct to send multiple data to the thread*/
    struct args *paramsThread = (struct args *)malloc(sizeof(struct args));
    
    printMatrix_DoublePointers(Ma, N, "Ma");
    printMatrix_DoublePointers(Mb, N, "Mb");
    
    /**
     * Struc to send multiple data to the threads
     * Variable assignment for struct
    **/
    paramsThread->size = N;
    paramsThread->nTh  = Nthreads;
    paramsThread->MA   = Ma;
    paramsThread->MB   = Mb;
    paramsThread->MC   = Mc;
    
	sampleStart();

    for (int i = 0; i < Nthreads; ++i){
        int *idThread = (int *)malloc(sizeof(int));
        *idThread = i;
        paramsThread->idTh = idThread;

        pthread_create(&threads[i], NULL, multMM, (void *)paramsThread);
    }
    
    for (int i = 0; i < Nthreads; ++i){        
        pthread_join(threads[i],NULL);
    }
    
    sampleEnd();
    free(threads);

    printMatrix_DoublePointers (Mc, N, "Mr");
    

	return EXIT_SUCCESS;
}
