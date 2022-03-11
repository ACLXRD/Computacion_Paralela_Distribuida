/*Fecha: 01/03/2022
* Autor: Andres C. Lopez R.
* Subject: Parallel and Distributed Computing.
* Topic: Poxis implemetation (Library)
* Description: Application for matrix multiplication
  with the calssical algorithm (rows x columns)
*/

/*Interfaces*/
#include "modulo.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

/*Define thread numbers according to the setup*/
#define MAX 4


/*Functions*/

/*	@brief: Print a matrix
	@param SZ: Size of the matrix
	@return *M: Matrix to print	
*/
void printMatrix(int SZ, int M[MAX][MAX]){
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


/*  @breif main(): Main function
*/
int main(){
    int mA[MAX][MAX];
    int mB[MAX][MAX];

    //Matrices's indices
    int f1 = MAX, c1 = MAX, f2 = MAX, c2 = MAX;        

    //Random number dor the matrices
    for (int i = 0; i < f1; i++){
        for (int j = 0; j < c1; j++){
            mA[i][j] = rand()%10;
            mB[i][j] = rand()%10;
        }    
    }

    //Print mA
    printf("Matriz A\n");

    printMatrix(f1, mA);

    //Print mB
    printf("Matriz B\n");
    printMatrix(f2, mB);


    int maxFC = f1*c1;      //Producto of (r*c)

    /*Declares the number of threads, size = maxFC */
    pthread_t *hilos;
    hilos = (pthread_t *)malloc(maxFC * sizeof(pthread_t)); 

    int contador = 0;
    int* dato = NULL;
    int z = 0; 

    for (int i = 0; i < f1; i++){
        for (int j = 0; j < c2; j++){       
            //Save rows and columns on datos (pointers)
            dato = (int *) malloc((20)*sizeof(int));
            dato[0] = c1;
            for (int k = 0; k < c1; k++){
                dato[k+1] = mA[i][k];
            }
            for (int k = 0; k < c1; k++){
                dato[k+c1+1] = mA[k][j];
            }
        //Thread creation
        pthread_create(&hilos[contador++], NULL, multiplication, (void *)(dato));
        }   
    } 

    /*M Result*/
    printf("Matris resultado\n");
    z = 0; 
	for (int i = 0; i < maxFC; i++){
        //Trheads join
        z++;
        void *k;
        pthread_join(hilos[i], &k);
        //Pointing p on k
        int *p = (int *)k;
        printf("%d  ", *p);
        
        if(z == f1){
            printf("\n");
            z = 0;
        }
    }
    return 0;
}