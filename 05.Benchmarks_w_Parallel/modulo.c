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
#include <omp.h>

/*CONSTANTS*/
struct timespec inicio, fin;

/* -------------------------------------Funciones ------------------------------------*/
/**
 * @brief: Get the init time
 */
void sampleStart()
{
	clock_gettime(CLOCK_MONOTONIC, &inicio);
}

/**
 * 	@brief: Get the end time
 */
void sampleEnd()
{
	clock_gettime(CLOCK_MONOTONIC, &fin);
	double totalTime;
	// char *unidad = "seg";
	totalTime = (fin.tv_sec - inicio.tv_sec) * 1e9;
	totalTime = (totalTime + (fin.tv_nsec - inicio.tv_nsec)) * 1e-9;

	// if (totalTime >= 60){
	// 	totalTime /= 60;
	// 	unidad = "min";
	// }
	// printf ("\nTotal time: %f %s \n\n", totalTime, unidad);

	printf("\n%f\n\n", totalTime);
}
/**
 * @brief: Function that generates a random number
 * @return: Random number between 0.001 and 9.999 with double precision
	---
	getpid(): Gets an ID of a rand porcess of the system
*/
double randNumber()
{
	float min = 0.001, max = 9.999;
	static int first = -1;
	if (first == (first < 0))
	{
		srand(time(NULL) + getpid());
	}
	if (min >= max)
	{
		return errno = EDOM, NAN;
	}
	return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

/**
 * @brief: Gives values for each space of a matrix
 * @param SZ: Size of the matrix
 */
void initMatrix(int SZ, double *Ma, double *Mb, double *Mr)
{
	int i, j;
	for (i = 0; i < SZ; ++i)
	{
		for (j = 0; j < SZ; ++j)
		{
			Ma[j + i * SZ] = 3.2 * (i + j);
			Mb[j + i * SZ] = 2.4 * (j - i);
			Mr[j + i * SZ] = 0.0;
		}
	}
}

/**
 * @brief: Print a matrix
 * @param SZ: Size of the matrix
 */
void printMatrix(int SZ, double *M, char *name)
{
	int i, j;
	if (SZ < 5)
	{
		printf("%s", name);
		for (i = 0; i < SZ; ++i)
		{
			for (j = 0; j < SZ; ++j)
			{
				printf("	%.2f", M[j + i * SZ]);
			}
			printf("\n");
		}
		printf("---------------------------------------------------------\n");
	}
}

/**
 * @brief: Print a matrix transposed
 * @param SZ: Size of the matrix
 */
void printMatrixTransposed(int SZ, double *M, char *name)
{
	int i, j;
	if (SZ < 5)
	{
		printf("%s", name);
		for (i = 0; i < SZ; ++i)
		{
			for (j = 0; j < SZ; ++j)
			{
				printf("	%.2f", M[j * SZ + i]);
			}
			printf("\n");
		}
		printf("---------------------------------------------------------\n");
	}
}

/**
 * @brief: Multiply matrices using row*columns
 * @param size: Size of matrix
 * @param a: Matriz A to multiply
 * @param b: Matriz B to multiply
 * @param c: Total matrix of multiplication
	---
*/
void MM1c(int size, double *Ma, double *Mb, double *Mr)
{
	int i, j;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			/*Necesita puteros auxiliares*/
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = Ma + (i * size);
			pB = Mb + j;
			for (int k = 0; k < size; ++k, pA++, pB += size)
			{
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i * size + j] = sumaAuxiliar;
		}
	}
}

/**
 * @brief: Multiply matrices using transposed matrix the way to multiply row*row
 * @param size: Size of matrix
 * @param Ma: Matriz A to multiply
 * @param Mb: Matriz B to multiply
 * @param Mr: Total matrix of multiplication
	---
*/
void MM1f(int size, double *Ma, double *Mb, double *Mr)
{
	int i, j, k;
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			/*Necesita puteros auxiliares*/
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = Ma + (i * size);
			pB = Mb + (j * size);
			for (k = 0; k < size; ++k, pA++, pB++)
			{
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i * size + j] = sumaAuxiliar;
		}
	}
}

/*	Se imlementa paso a paso benchmark Multiaplicacion de matrices
	Algoritmo clasico (filas x columnas) de matrices
	de igual diemnsion
*/

/****************** Functions for posix (program using threads)**************************/

/**
 * @breif: Memory reserve for double pointer matrices
 * @param size: Matrix size
 * @return ptr: Doble pointer Vector with portions of the matrix allocated in threads
 */
double **memReserve(int size)
{
	/* Memory reserve of dimenion NxN double*/
	double *val = (double *)malloc(size * size * sizeof(double));

	/* Doble pointer Vector reserve of dimenion size*/
	double **ptr = (double **)malloc(size * size * sizeof(double *));
	/* Iteration with the purpose that each pointer position itself in the memory reserve*/
	for (int i = 0; i < size; ++i)
	{
		ptr[i] = &val[i * size];
	}
	return ptr;
}

/**
 * @brief: Gives values for each space of a matrix
 * @param MA: Matrix A
 * @param MB: Matrix B
 * @param MC: Matrix C
 * @param size: Size of the matrix
 */
void initMatrix_DoublePointers(double **MA, double **MB, double **MC, int size)
{
	int i, j; /*Indices*/
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			MA[i][j] = 3.2 * (i + j);
			MB[i][j] = 2.4 * (i - j);
			MC[i][j] = 0.0;
		}
	}
}

/**
 * @brief Fuction to print matrix of type double pointer
 * @param M: matrix of type double pointer to print
 * @param size: Matrizx size
 */
void printMatrix_DoublePointers(double **M, int size, char *name)
{
	int i, j; /*Indices*/
	if (size < 5)
	{
		printf("%s", name);
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				printf("	%.2f", M[i][j]);
			}
			printf("\n");
		}
		printf("----------------------------------------------------------\n");
	}
}

/**
 * Struc to send multiple data to the threads
 * size: Matrix size
 * nTh: Number of threads
 * idTh: Thread ID
 * MA: Matrix A
 * MB: Matrix B
 * MC: Matrix C (result of multiplication)
 */

/**
 * @brief Function that will be sent to each thread, that makes the matrix multiplication.
 * The matrix A divides in slices, in function with the dimension and the number of threads that requires the
 * user.
 * @param arg: Alocate the struct args sent at the interface.
 * Note: 	The function will be void, and this returns a potential
 * 			warning. Thats why the we use return NULL.
 */
void *multMM(void *arg)
{
	int N = ((struct args *)arg)->size;
	int Nthreads = ((struct args *)arg)->nTh;
	double **Ma = ((struct args *)arg)->MA;
	double **Mb = ((struct args *)arg)->MB;
	double **Mc = ((struct args *)arg)->MC;
	int idTh = *((struct args *)arg)->idTh; // Void pointer to integer

	int i, j, k;
	int portionSize, initRow, endRow;
	double sum;

	portionSize = N / Nthreads;		   // It is determined the portion of matrix A to send to each thread
	initRow = idTh * portionSize;	   // It is passed the beggining of the row
	endRow = (idTh + 1) * portionSize; // It is passed the end of the row

	for (i = initRow; i < endRow; i++)
	{
		for (j = 0; j < N; ++j)
		{
			sum = 0;
			for (k = 0; k < N; k++)
			{
				sum += Ma[i][k] * Mb[k][j];
			}
			Mc[i][j] = sum;
		}
	}
	// pthread_exit(NULL);
	return NULL;
}

/****************** Functions for the implementation of OMP **************************/

/**
 * @brief Function that makes the matrix multiplication between two matrixes
 * 		  and the result is saved in another matrix. Using OMP
 *
 * @param size  Matrix size
 * @param Ma Matrix A
 * @param Mb Matrix B
 * @param Mr Result matrix
 */
void MM1c_OMP(int threads, int size, double *Ma, double *Mb, double *Mr)
{
	omp_set_num_threads(threads);
/*Instruction to the compiler, telling that here starts the
parallel computation*/
#pragma omp parallel
	{
		int i, j, k;
#pragma omp for
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				/*Necesita puteros auxiliares*/
				double *pA, *pB;
				double sumaAuxiliar = 0.0;
				pA = Ma + (i * size);
				pB = Mb + j;
				for (k = 0; k < size; ++k, pA++, pB += size)
				{
					sumaAuxiliar += (*pA * *pB);
				}
				Mr[i * size + j] = sumaAuxiliar;
			}
		}
	}
}

/**
 * @brief Function that makes the matrix multiplication between two matrixes
 * 		  and the result is saved in another matrix. Using OMP
 *
 * @param size  Matrix size
 * @param Ma Matrix A
 * @param Mb Matrix B
 * @param Mr Result matrix
 */
void MM1f_OMP(int threads, int size, double *Ma, double *Mb, double *Mr)
{
	omp_set_num_threads(threads);
/*Instruction to the compiler, telling that here starts the
parallel computation*/
#pragma omp parallel
	{
		int i, j, k;
#pragma omp for
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				/*Necesita puteros auxiliares*/
				double *pA, *pB;
				double sumaAuxiliar = 0.0;
				pA = Ma + (i * size);
				pB = Mb + (j * size);
				for (k = 0; k < size; ++k, pA++, pB++)
				{
					sumaAuxiliar += (*pA * *pB);
				}
				Mr[i * size + j] = sumaAuxiliar;
			}
		}
	}
}
