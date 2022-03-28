/*Fecha: 08/02/2022
* Autor: Andres C. Lopez R.
* Subject: Parallel and Distributed Computing.
* Topic: Construction of the first Benchmark
* Description: Application that allows evaluating the performance
  of a specific aspect of the computer using matrix multiplication
  with the calssical algorithm (rows x columns)
*/

/*Interfaces*/

#include "modulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>


/*CONSTANTS*/
struct timespec inicio, fin;

/* -------------------------------------Funciones ------------------------------------*/
/*	@brief: Get the init time*/
void sampleStart(){
	clock_gettime(CLOCK_MONOTONIC, &inicio);	
}

/*	@brief: Get the end time */
void sampleEnd(){
	clock_gettime(CLOCK_MONOTONIC, &fin);	
	double totalTime;
	char *unidad = "seg";
	totalTime 	= (fin.tv_sec - inicio.tv_sec)*1e9;
	totalTime	= (totalTime + (fin.tv_nsec - inicio.tv_nsec))*1e-9;

	if (totalTime >= 60){
		totalTime /= 60;
		unidad = "min"; 
	}

	printf ("\nTotal time: %f %s \n\n", totalTime, unidad);
}
/*	@brief: Function that generates a random number 
	@return: Random number between 0.001 and 9.999 with double precision
    ---
    getpid(): Gets an ID of a rand porcess of the system
*/
double randNumber(){
    float min = 0.001, max = 9.999;
    static int first = -1;
    if(first == (first < 0)){
       srand(time(NULL) + getpid());
    }
    if(min >= max){
        return errno = EDOM, NAN;
    }
    return min + (float)rand()/((float)RAND_MAX/(max-min));
}

/*	@brief: Gives values for each space of a matrix
	@param SZ: Size of the matrix

*/
void initMatrix(int SZ, double *Ma, double *Mb, double *Mr){
	int i, j;
	for(i=0; i<SZ; ++i){
		for(j=0;j<SZ;++j){
			Ma[j+i*SZ] = randNumber();
			Mb[j+i*SZ] = randNumber();
			Mr[j+i*SZ] = 0.0;
		}
	}
}

/*	@brief: Print a matrix
	@param SZ: Size of the matrix
	@return *M: Matrix to print	
*/
void printMatrix(int SZ, double *M){
	int i,j;
	for (i=0;i<SZ; ++i){
		for (j=0;j<SZ; ++j){
			printf("  %f  ",M[j+i*SZ]);
		}
		printf("\n");
	}
		printf("----------------------------");
		printf("\n");
		
		
}

/*	@brief: Multiply matrices
	@param size: Size of matrix
	@param a: Matriz A to multiply
	@param b: Matriz B to multiply
	@param c: Total matrix of multiplication
    ---
*/
void matrixMultiplyMM1c(int size, double *Ma, double *Mb, double *Mr){
	int i, j;
	for(i=0; i<size; ++i){
		for(j=0; j<size; ++j){
		/*Necesita puteros auxiliares*/
		double *pA, *pB;
		double sumaAuxiliar = 0.0;
		pA = Ma + (i*size);
		pB = Mb + j;
			for(int k = 0; k < size; ++k, pA++, pB += size){
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i*size+j] = sumaAuxiliar;
		}
	}
}

void matrixMultiplyMM1f(int size, double *Ma, double *Mb, double *Mr){
  int i, j;
	for(i=0; i<size; ++i){
		for(j=0; j<size; ++j){
		/*Necesita puteros auxiliares*/
		double *pA, *pB;
		double sumaAuxiliar = 0.0;
		pA = Ma + (i*size);
		pB = Mb + (j*size);
			for(int k = 0; k < size; ++k, pA++, pB++){
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i*size+j] = sumaAuxiliar;
		}
	}
}

/*	Se imlementa paso a paso benchmark Multiaplicacion de matrices
	Algoritmo clasico (filas x columnas) de matrices
	de igual diemnsion
*/


/****************** Functions for posix (program using threads)**************************/

/*
	@breif: Memory reserve for double pointer matrices
	@param size: Matrix size
	@return ptr: Doble pointer Vector with portions of the matrix allocated in threads
*/
double ** memReserve (int size){
	/* Memory reserve of dimenion NxN double*/
	double *val = (double *) malloc(size*size*sizeof(double));

	/* Doble pointer Vector reserve of dimenion size*/
	double ** ptr = (double **) malloc(size*size*sizeof(double *));
	/* Iteration with the purpose that each pointer position itself in the memory reserve*/
	for (int i = 0; i < size; ++i)	{
		ptr[i] = &val[i*size];
	}
	return ptr;
}

/*	@brief: Gives values for each space of a matrix
	@param **Ma: Matrix A
	@param **Mb: Matrix B
	@param **Mc: Matrix C
	@param size: Size of the matrix
*/
void initMatrix_DoublePointers (double **MA, double **MB, double **MC, int size){
	int i, j; /*Indices*/
	for (i = 0; i < size; ++i)	{
		for (j = 0; j < size; ++j)	{
			MA[i][j] = randNumber();
            MB[i][j] = randNumber();
            MC[i][j] = 0.0;
		}
	}
}

/*
* @brief Fuction to print matrix of type double pointer
* @param **M: matrix of type double pointer to print
* @size: Matrizx size
*/
void printMatrix_DoublePointers (double **M, int size){
	int i, j; /*Indices*/
	for (i = 0; i < size; ++i)	{
		for (j = 0; j < size; ++j)	{
			printf("	%lf", M[i][j]);
		}
		printf("\n");
	}
	printf("-----------------------------\n");

}

/*Struc to send multiple data to the threads
    size: Matrix size
    nTh: Number of threads
    idTh: Thread ID
    MA: Matrix A
    MB: Matrix B
    MC: Matrix C (result of multiplication)
*/
struct args {
    int size, nTh;
    int *idTh;
    double **MA, **MB, **MC;
};

/**
 * @brief Function that will be sent to each thread, that makes the matrix multiplication.
 * The matrix A divides in slices, in function with the dimension and the number of threads that requires the 
 * user.
 * @param arg: Alocate the struct args sent at the interface.
 * Note: 	The function will be void, and this returns a potential 
 * 			warning. Thats why the we use return NULL.
 */
void *multMM(void *arg){
	int N 		=  ((struct args*)arg)->size;
	int Nthreads=  ((struct args*)arg)->nTh; 
	double **Ma =  ((struct args*)arg)->MA;
	double **Mb	=  ((struct args*)arg)->MB;
	double **Mc	=  ((struct args*)arg)->MC;
	int idTh	= *((struct args*)arg)->idTh; 	//Void pointer to integer 

	int i, j, k;
	int portionSize, initRow, endRow;
	double sum;
	
	portionSize = N/Nthreads; 		// It is determined the portion of matrix A to send to each thread
	initRow = idTh*portionSize; 	// It is passed the beggining of the row 
	endRow = (idTh+1)*portionSize;	// It is passed the end of the row
	
	for (i = initRow; i < endRow; i++){
		for (j = 0; j < N; ++j){
			sum = 0;
			for ( k = 0; k < N; k++){
				sum += Ma[i][k]*Mb[k][j];
			}
			Mc[i][j] = sum;
		}
	}
	
	return NULL;
}
