/*
 Autor: Andrés C. López
 Materia: Computación Paralela y Distribuida.
 Tema: Talle 1 en C++
 Descripción: Programa que defina el importe de 
 vehiculos seleccionados.
*/

/* Declaración de interfaces: */
#include <iostream>
#include <cctype>

/*Declaración del espacio de dominio */
using namespace std;

/*Funciones*/

/*
	@breif: km () captura el valor del kilometraje
	@return k: Kilometraje ingresado
*/
int km (){
	cout << "kilometros: ";
	int k = 0;
	cin >> k;
	return k;
}

/*
	@breif: ton () captura las toneladas
	@return t: Toneladas ingresadas
*/
int ton (){
	cout << "Toneladas: ";
	int t = 0;
	cin >> t;
	return t;
}

int main (){
	int op = 0, importe = 0;
	cout << "1- Bicicleta\n2- Moto\n3- Coche\n4- Camion \n5- Salir\n\nOpcion: ";
	cin >> op;
	
	switch (op){
		case 1:
			importe = 100;
			break;
		case 2:
			importe = 30*(km());
			break;
		case 3:
			importe = 30*(km());
			break;
		case 4:
			importe = 30*(km()) + 25*(ton());
			break;	
		case 5:
			exit(0);
			break;
	}
	cout << "Importe = " << importe;
}

