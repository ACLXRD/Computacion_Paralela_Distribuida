/*
 Autor: Andrés C. López
 Materia: Computación Paralela y Distribuida.
 Tema: Talle 1 en C++
 Descripción: Aplicación que permita evaluar una
 serie donde 1/x+ay.
*/

/* Declaración de interfaces: */
#include <iostream>


/*Declaración del espacio de dominio */
using namespace std;

/*Funciones*/

int main(){
	int a = 0;
	float b = 0, x = 0, y = 0, r = 0;
	cout << "--- Serie de 1/(x+ay) ---\n" << endl;
	
	cout << "Ingresa el limite de la serie: ";
	cin >> a;
	
	cout << "\nIngresa el valor de la constante x: ";
	cin >> x;
	
	cout << "\nIngresa el valor de la constante y: ";
	cin >> y;
	cout << "\nInicio de la sumatorioa:" << endl;
	
	for (b = 0; b <= a; b++){
		r += 1/(x+(b*y));
		cout << "a: " << b << " - Serie = " << 1/(x+(b*y)) << endl;
	}
	
	cout << "\nResultado: " << r << endl;
}
