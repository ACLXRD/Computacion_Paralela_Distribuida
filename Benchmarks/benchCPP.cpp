 
/*Fecha: 3/02/2022
* Autor: Andres C. Lopez R.
* Subject: Parallel and Distributed Computing.
* Topic: Construction of the first Benchmark
* Description: Application that allows evaluating the performance
  of a specific aspect of the computer using matrix multiplication
  with the calssical algorithm (rows x columns)
*/


//Interfaces
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <unistd.h>
#include <math.h>

//Domain space
using namespace std;

//CONSTANTS
struct timespec inicio, fin;

/* ----------------------------- -------Funciones ------------------------------------*/

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
	cout << "\nTotal time: " << totalTime << " seg";
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
vector<vector<double>> matrixInit(int size){
	int i, j;
	vector<vector<double>> MI(size, vector<double> (size,0)); 
    	
	for (i=0; i<size; ++i){
		for (j=0; j<size; ++j){
			MI[i][j] = randNumber();
		}
	}
	return MI;	
}

/*	@brief: Multiply matrices
	@param MA: Matriz A to multiply
	@param MB: Matriz B to multiply
    ---
*/
void matrixMultiply (vector<vector<double>> MA, vector<vector<double>>MB){
	int i, j, k;
	vector<vector<double>> MT (MA.size(), vector<double> (MA.size(),0));;
	
	for(i = 0; i<MA.size(); ++i){
		for(j = 0; j<MA.size(); ++j){
			for(k = 0; k<MA.size(); ++k){
				MT[i][j] += MA[i][k]*MB[k][j];
			}
		}
	}	
}

int main (int argc, char** argv) {
	int k;
	int N = atoi(argv[1]);
	
	//Se utiliza la calse vector para crear las matrices
	//Matrix of size N full of 0
	vector<vector<double>> M1(N, vector<double> (N,0)); 
	vector<vector<double>> M2(N, vector<double> (N,0));
	vector<vector<double>> MR(N, vector<double> (N,0));
	
	//Matrix init
	M1 = matrixInit(N);
	M2 = matrixInit(N);	
	
	sampleStart();
	matrixMultiply(M1, M2);
	sampleEnd();
	return 0;
}

/*
Compile
	g++ main_bench01.cpp
Execute
	time ./a.out N--> N : Any number
*/
