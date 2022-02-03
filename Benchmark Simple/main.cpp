/*Fecha: 1/02/2022
* Autor: Andr�s C. L�pez
* Materia: Computaci�n Paralela y Distribuida.
* Tema: Mini Benchmark 
* Descripci�n: Aplicaci�n para medir rendimiento.
*/

/* Declaraci�n de interfaces: */
#include <iostream>

/*Se declara el espacio de dominio */
using namespace std;

/*Se define una constante*/
#define size 32768


/*Loop para determinar el tiempo de acceso de datos*/

int main () {
	int matrix[size][size];
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			matrix[i][j] = 47;		
		}
	}
	return 0;
}
