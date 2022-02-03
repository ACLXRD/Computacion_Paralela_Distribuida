/*Fecha: 1/02/2022
* Autor: Andrés C. López
* Materia: Computación Paralela y Distribuida.
* Tema: Mini Benchmark 
* Descripción: Aplicación para medir rendimiento.
*/

/* Declaración de interfaces: */
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
