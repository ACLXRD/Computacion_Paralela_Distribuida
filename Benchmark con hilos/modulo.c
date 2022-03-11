/*  Fecha: 01/03/2022
*   Autor: Andres C. Lopez R.
*   Subject: Parallel and Distributed Computing.
*   Topic: Poxis implemetation (Library)
*   Description: This module implements the 
    threats which calculate the product of the 
    matrix. The aplication has to be modular
*/

/*Interfaces*/

#include "modulo.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

/*Each thread calculates a single element over the result matrix */

/*  @brief *multiplication(): Function that implements the matrix 
    multiplication .
    @param *arg: Pointer to the data vector.
    @varaible *datos: Data vector is a peace send to the calculation 
    for the calc dor the result matrix.
*/
void *multiplication(void *arg){
    int *datos = (int *)  arg;  //Data vector
    int i, j, k;                //Indices
    int x = datos[0];           //Vector's first value 
    
    for (i = 1; i <= x ; i++){
        k += datos[i] * datos [i+x];    
    }

    int *p = (int *) malloc(sizeof(int));   //Memory backup for a pointer
    *p = k;                                 
    pthread_exit(p);
}

/*void printMatrix(int SZ, int M){
	int i,j;
	for (i = 0; i < SZ; i++){
        for (j = 0; j < SZ; j++){
            printf("%d  ", M[i][j]);
        }    
        printf("\n");
    }
        printf("\n");
        printf("\n");
}
*/