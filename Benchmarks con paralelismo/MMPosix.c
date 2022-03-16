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
        4.1.2 The matrix's size will be sent in the 
        execution.
    5. Matrix's size always squared (NxN)
    6.  Print matrix with double pointer.
*/


/*Interfaces*/
#include "modulo.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

/*Global variables*/
int N, Nthreads;
double **Ma, **Mb, **Mc;

/*  @breif main(): Main function
*/
int main(int argc, char* argv[]){
    /*Init of global variables*/
    N           = atof(argv[1]);    /* Matrix's size.*/
    Nthreads    = atof(argv[2]);    /* Number of threads.*/

    /*Memory creation and reserce for each matrix*/
    Ma = memReserve(N); 
    Mb = memReserve(N);
    Mc = memReserve(N);
    initMatrix_DoublePointers (Ma, Mb, Mc, N);
    printMatrix_DoublePointers (Ma, N);
    printMatrix_DoublePointers (Mb, N);
    printMatrix_DoublePointers (Mc, N);

    return 0;
}