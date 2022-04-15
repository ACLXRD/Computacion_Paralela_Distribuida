/*Fecha: 22/02/2022
* Autor: Andres C. Lopez R.
* Subject: Parallel and Distributed Computing.
* Topic: Construction Benchmark using reference
* Description: Application that allows evaluating the performance
  of a specific aspect of the computer using matrix multiplication
  with the calssical algorithm (rows x columns) 
*/

//Interfaces
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <random>
#include <chrono>
#include <ctime>

//Domain space
using namespace std;

//CONSTANTS
struct timespec inicio, fin;
/* ----------------------------- -------Funciones ------------------------------------*/

/*	@brief: Get the start time */
void sampleStart(){
	clock_gettime(CLOCK_MONOTONIC, &inicio);	
}

/*	@brief: Get the end time */
void sampleEnd(){
	clock_gettime(CLOCK_MONOTONIC, &fin);	
	double totalTime;
	totalTime = (fin.tv_sec - inicio.tv_sec)*1e9;
	totalTime = (totalTime + (fin.tv_nsec - inicio.tv_nsec))*1e-9;
	cout << "\nTotal time: " << totalTime << " seg" << endl;
}


//  @brief: Function that generates a random number 
//	@return: Random number between 0.001 and 9.999 with double precision
//    --- getpid(): Gets an ID of a rand porcess of the system
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

//  @breif initMatrix() : Function to initializate a matrix.
//  @param size: Sie of the matrix.
//  @param &m1: The pointer of the first matrix.
//  @param &m2: The pointer of the second matrix.
//  @param &m3: The pointer of the third matrix.
// --this params with "&" refers to the direction af the matrix.
void initMatrix (int size, double** &m1, double** &m2, double** &m3){
    int i, j; //indices

    for (i = 0; i < size; ++i){     //rows
        for (j = 0; j < size; ++j){ //columns  
            m1[i][j] = randNumber();
            m2[i][j] = randNumber();
            m3[i][j] = 0;
        }
    }    
}

//  @breif createMatrix() : Function to create matrix
//  @param size: Sie of the matrix to create
// @return matrix: The matriz created
double**  createMatrix(int size){
    int i;
    double **matrix = new double* [size*size];
    //Inside a containter, we insert a nuex container using the pointers, "box into a box"
    for (i = 0; i < size; ++i){       //second pointer
        matrix[i] = new double [size]();
    }
    return matrix;
}

//	@brief matrixMultiply(): Multiply matrices using clasic algorith (rows x columns)
//  @param &m1: The pointer of the first matrix.
//  @param &m2: The pointer of the second matrix.
//  @param &m3: The pointer of the third matrix, the result  of the multiplication.

void matrixMultiply (int size, double** &m1, double** &m2, double** &m3 ){
	int i, j, k;
	
	for(i = 0; i < size; ++i){          //rows
		for(j = 0; j < size; ++j){      //columns
			for(k = 0; k < size; ++k){  //product = (rows x columns)
				m3[i][j] += m1[i][k]*m2[k][j];
			}
		}
	}	
}


//  @breif printMatrix() : Function to print matrix.
//  @param size: Sie of the matrix.
// @param &matrix: Reference of te matrix to print.
void printMatrix (double** &matrix, int size){
    int i, j;
	for (i = 0; i < size; ++i){         //rows
		for (int j=0; j < size; ++j){   //columns
			cout << matrix[i][j] << "    ";
		}
		cout << "\n";
	}	
	cout << "\n\n";
}

//  @breif printMatrix() : Function to break free the memory taht use a matrix.
//  @param size: Sie of the matrix.
// @param &matrix: Reference of te matrix to delete.
void destroyMatrix (double** &matrix, int size){
    if (matrix){
        int i;
        for (i = 0; i < size; ++i){         //rows
            delete[] matrix[i];  //Deleting each row    
        }
        delete[] matrix;         //Deleting all the rows
        matrix = nullptr;        //Returning memory to system.
    }
}

//@ breif main():Main fuction
int main(int argc, char *argv[]){
    int i, j, k, N = atoi(argv[1]);
    // i, j and k: indices
    // N: Size of the matrix

    double **matA = createMatrix(N);
    double **matB = createMatrix(N);
    double **matC = createMatrix(N);
    
    initMatrix(N, matA, matB, matC);

    /*cout << "Matrix A" << endl;
    printMatrix(matA, N);
    cout << "Matrix B" << endl;
    printMatrix(matB, N);
    */
    sampleStart();
    matrixMultiply(N, matA, matB, matC);
	sampleEnd();
    
    /*cout << "Result Matrix" << endl;
    printMatrix(matC, N);*/
        
    // Return used memory tio system. (Detroting the matrices)
    destroyMatrix(matA, N);
    destroyMatrix(matB, N);
    destroyMatrix(matC, N);

    return 0;
}

/*
Compile
    g++ becnchCpp_reference.cpp -o exe
Execute 
    time ./exe 400
*/