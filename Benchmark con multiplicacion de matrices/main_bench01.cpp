 
/*Fecha: 3/02/2022
* Autor: Andrés C. López
* Materia: Computación Paralela y Distribuida.
* Tema: Construcción del primer Benchmark 
* Descripción: Aplicación que permite evaluar el rendimiento
  de un aspecto en específico del ordenador
* Ejercicio: Se requiere implementar una aplicación que multiplique dos matrices.
  el algoritmo a usar será e clásico (filas por columnas).
  Las matrices deben ser de doble presición.
*/

/* Declaración de interfaces*/
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <chrono>

/*Declaración del espacio de dominio*/
using namespace std;

/*Definición de constantes*/


/*Funciones*/
void printMatrix (vector<vector<double>> M, string name){
	
	cout << name << endl;
	for (int i=0; i<M.size(); ++i){
		for (int j=0; j<M.size(); ++j){
			cout << M[i][j] << "    ";
		}
		cout << "\n";
	}	
	cout << "\n";
}

/*	@brief: Function that generates a random number 
	@param min: Lower limit
	@return
*/
double randNumber(double min, double max){
	double f = (double)rand() / RAND_MAX;
	return min + f* (max - min);
}

/** Inialización de las matrices con número aleatoreos*/
vector<vector<double>> matrixInit(vector<vector<double>> M){
	vector<vector<double>> MI(M.size(), vector<double> (M.size(),0)); 
	double limInf = 0.001, limSup = 9.999;
//	random_device rd;
//    mt19937 gen(rd());
//    uniform_real_distribution<double> dis(limInf, limSup);
    	
	for (int i=0; i<M.size(); ++i){
		for (int j=0; j<M.size(); ++j){
			/*MI[i][j] = dis(gen);*/
			//MI[i][j] = limInf + (double)(rand()) / ((double)(RAND_MAX/(limInf - limSup)))*-1;
			MI[i][j] = randNumber(limInf, limSup);
		}
	}
	return MI;	
}

/** Multiplicación de matrices*/
vector<vector<double>> matrixMultiply (vector<vector<double>> MA, vector<vector<double>>MB){
	vector<vector<double>> MT (MA.size(), vector<double> (MA.size(),0));;
	//Inicia punta de prueba para tomar tiempo inicial
	auto startTime = chrono::high_resolution_clock::now();
	/*auto se utiliza cuando no se sabe que tipo de dato será la variable.*/
	for(int i = 0; i<MA.size(); ++i){
		for(int j = 0; j<MA.size(); ++j){
			for(int k = 0; k<MA.size(); ++k){
				MT[i][j] += MA[i][k]*MB[k][j];
			}
		}
	}
	//Inicia punta de prueba para tomar tiempo final
	auto endTime = chrono::high_resolution_clock::now();
	chrono::duration<double, milli>  tiempoTotal = endTime - startTime;
	
	cout << "Tiempo empleado: " << tiempoTotal.count() << "ms" <<  endl;
	
	return MT;
}

int main (int argc, char** argv) {
	int k;
	int N = atoi(argv[1]);
	cout << "\nMatrix's size: " << N << "x" << N << "\n" << endl;
	
	/* Se utiliza la calse vector para crear las matrices */
	/*** Matriz de tamaño NxN compuesta por vectores de tamaño N con el dato 0 en todas sus posiciones*/
	vector<vector<double>> M1(N, vector<double> (N,0)); 
	vector<vector<double>> M2(N, vector<double> (N,0));
	vector<vector<double>> MR(N, vector<double> (N,0));
	
	/*Inialización de las matrices con número aleatoreos*/
	M1 = matrixInit(M1);
	M2 = matrixInit(M2);	
	
	/*Multiplicación de matrices M1 y M2
	Se debe validar que el algoritmo de multiplicación funcione*/
	MR = matrixMultiply(M1, M2);

	/*Se imprime M1*/
//	printMatrix(M1, "Matrix 1");
//		
//	/*Se imprime M2*/
//	printMatrix(M2, "Matrix 2");
//	
//	/*Se imprime MR*/
//	printMatrix(MR, "Matrix R");

	return 0;
}

