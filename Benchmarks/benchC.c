/*Fecha: 08/02/2022
* Autor: Andres C. Lopez R.
* Subject: Parallel and Distributed Computing.
* Topic: Construction of the first Benchmark
* Description: Application that allows evaluating the performance
  of a specific aspect of the computer using matrix multiplication
  with the calssical algorithm (rows x columns)
*/

/*Interfaces*/

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
	totalTime = (fin.tv_sec - inicio.tv_sec)*1e9;
	totalTime = (totalTime + (fin.tv_nsec - inicio.tv_nsec))*1e-9;
	printf ("\nTotal time: %f seg \n", totalTime);
}

/*	@brief: Function that generates a random number 
	@return: Random number between 0.001 and 9.999 with double precision
    ---
    getpid(): Gets an ID of a rand porcess of the system
*/
double randNumber(){
    float min = 0.001, max = 9.999;
    static int first = -1;
    if(first = (first < 0)){
       srand(time(NULL) + getpid());
    }
    if(min >= max){
        return errno = EDOM, NAN;
    }
    return min + (float)rand()/((float)RAND_MAX/(max-min));
}

/*	@brief: Gives values for each space of a matrix
	@param size: Size of the matrix
	@return MI: Matrix with values in its spaces	
*/
void InitMatrix(int SZ, double *Ma, double *Mb, double *Mr){
    int i,j,k;
    for(i=0; i < SZ; ++i){
        for(j=0;j<SZ;++j){
            Ma[j+i*SZ] = randNumber();
            Mb[j+i*SZ] = randNumber();
            Mr[j+i*SZ] = 0.0;
        }
    }
}

/*Varaible of high value to reserve memory*/
#define DATA_SZ (1024*1024*64*3)

/*Memory space acordin reserve memory value*/
static double MEM_CHUNK[DATA_SZ];

/*	@brief: Gives values for each space of a matrix
	@param size: Size of the matrix
	@return MI: Matrix with values in its spaces	
*/
void initMatrix(int SZ, double *Ma, double *Mb, double *Mr){
	int i, j, k;
	for(i=0; i<SZ; ++i){
		for(j=0;j<SZ;++j){
			Ma[j+i*SZ] = 3.0*(i-j);
			Mb[j+i*SZ] = 2.8*(j+i);
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
		
}

/*	@brief: Multiply matrices
	@param size: Size of matrix
	@param a: Matriz A to multiply
	@param b: Matriz B to multiply
	@param c: Total matrix of multiplication
    ---
*/
void matrixMultiply (int size, double *Ma, double *Mb, double *Mr){
	int i, j, k;
	for(i=0; i<size; ++i){
		for(j=0; j<size; ++j){
		/*Necesita puteros auxiliares*/
		double *pA, *pB;
		double sumaAuxiliar = 0.0;
		pA = Ma + i;
		pB = Mb + j;
			for(k = 0; k < size; ++k, pA += size, pB++){
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[j*size+i] = sumaAuxiliar;
		}
	}
}

/*	Se imlementa paso a paso benchmark Multiaplicacion de matrices
	Algoritmo clasico (filas x columnas) de matrices
	de igual diemnsion
*/
int main(int argc, char *argv[]) {
	
	/*Matrix size*/
	int N = (int) atof(argv[1]);
	
	/*Apuntamos los vectores (creacion) a espacio de memoria reservada con dimension NxN */
	double *Ma, *Mb, *Mr;
	Ma = MEM_CHUNK;
	Mb = Ma + N*N;
	Mr = Mb + N*N;
	
	initMatrix(N, Ma, Mb, Mr);
	sampleStart();
	matrixMultiply(N, Ma, Mb, Mr);
	sampleEnd();
		
	return 0;
}
/*
Compile
	gcc main_bench.c -o mmSerieC
Execute
	time ./a.out N--> N : Any number
*/
