/* 
	Fecha: 08 de febrero de 2022
	Autor: Andr�s C. L�pez R.
	Materia: Computaci�n Paralela y Distribuida
	Tema: Aplicaci�n que permite evaluar el rendimiento
  	de un aspecto en espec�fico del ordenador
 	Descripci�n: Se requiere implementar una aplicaci�n que multiplique dos matrices.
  	el algoritmo a usar ser� e cl�sico (filas por columnas).
  	Las matrices deben ser de doble presici�n.
*/


#include <stdio.h>
#include <stdlib.h>

// Se crea una variable con un valor alto para reservar memoria
#define DATA_SZ (1024*1024*64*3)

// Se reserva el espacio de memoria segun el valor
static double MEM_CHUNK[DATA_SZ];

//Se crea la funcion para incializar las matrices
void InitMatrix(int SZ, double *Ma, double *Mb, double *Mr){
	int i,j,k;
	for(i=0;i<SZ;++i){
		for(j=0;j<SZ;++j){
			Ma[j+i*SZ] = 3.0*(i-j);
			Mb[j+i*SZ] = 2.8*(j+i);
			Mr[j+i*SZ] = 0.0;
		}
	}
		
}

// Se impleenta la impresi�n (Para efectos de validaci�n)
void printMatrix(int SZ, double *M){
	int i,j;
	for (i=0;i<SZ; ++i){
		for (j=0;j<SZ; ++j){
			printf("  %f  ",M[j+i*SZ]);
		}
		printf("\n");
	}
		
}

/*	Se imlementa paso a paso benchmark Multiaplicacion de matrices
	Algoritmo cl�sico (filas x columnas) de matrices
	de igual diemnsi�n
*/
int main(int argc, char *argv[]) {
	
	/*Se captura la dimensi�n de la matriz*/
	int N = (int) atof(argv[1]);
	printf("Valor ingresado %d", N);
	
	// Apuntamos los vectores (creaci�n) a espacio de memoria reservada con dimensi�n NxN
	double *Ma, *Mb, *Mr;
	Ma = MEM_CHUNK;
	Mb = Ma + N*N;
	Mr = Mb + N*N;
	
	InitMatrix(N, Ma, Mb, Mr);
	printf("\n Matriz A \n");
	printMatrix(N,Ma);
	printf("\n Matriz B \n");
	printMatrix(N,Mb);
	
	int i,j,k;
	for(i=0;i<N;++i){
		for(j=0;j<N;++j){
		// Necesita puteros Auxiliares
		double *pA, *pB;
		double sumaAuxiliar = 0.0;
		pA = Ma + (i*N);
		pB = Mb + j;
			for(k=0;k<N;++k, pA++, pB+=N){
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i*N+j] = sumaAuxiliar;
		}
	}
	
	printf("\n Matriz Mr \n");
	printMatrix(N,Mr);
		
	return 0;
}
