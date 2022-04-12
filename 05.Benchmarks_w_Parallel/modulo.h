/**Fecha: 08/02/2022
* Autor: Andres C. Lopez R.
* Subject: Parallel and Distributed Computing.
* Topic: Construction of the first Benchmark
* Description: Application that allows evaluating the performance
  of a specific aspect of the computer using matrix multiplication
  with the calssical algorithm(rows x columns)
*/

#ifndef MODULO_C_H_INCLUDE
#define MODULO_C_H_INCLUDE

/**
 * Struc to send multiple data to the threads
 * size: Matrix size
 * nTh: Number of threads
 * idTh: Thread ID
 * MA: Matrix A
 * MB: Matrix B
 * MC: Matrix C(result of multiplication)
*/
struct args {
    int size, nTh;
    int *idTh;
    double **MA, **MB, **MC;
};


void sampleStart();
void sampleEnd();
double randNumber();
double ** memReserve(int size);
void initMatrix(int SZ, double *Ma, double *Mb, double *Mr);
void printMatrix(int SZ, double *M, char *name);
void printMatrixTransposed(int SZ, double *M, char *name);
void initMatrix_DoublePointers(double **MA, double **MB, double **MC, int size);
void printMatrix_DoublePointers(double **M, int size, char *name);
void MM1c(int size, double *Ma, double *Mb, double *Mr);
void MM1f(int size, double *Ma, double *Mb, double *Mr);
void *multMM(void *arg);
void MM1c_OMP(int threads, int size, double *Ma, double *Mb, double *Mr);
void MM1f_OMP(int threads, int size, double *Ma, double *Mb, double *Mr);

#endif
