/*
 Autor: Andr�s C. L�pez
 Materia: Computaci�n Paralela y Distribuida.
 Tema: Talle 1 en C++
 Descripci�n: Aplicaci�n que calcule la suma 
 de los multiplos de 5 dado un intervalo con
 limites positivos.
*/

/* Declaraci�n de interfaces: */
#include <iostream>
#include <tuple>
#include <cctype>

/*Declaraci�n del espacio de dominio */
using namespace std;

/*Funciones*/

/** positiveOnly:  Recive un parametro de tipo string.
	Verifica que el n�mero ingresado sea positivo.
	Retorna un n�mero positivo.*/
int positiveOnly (string txt){
	int x = -1;
	while (x < 0){
		cout << txt;
		cin >> x;
		if (isdigit(x)){
			cout << "Debes ingresar un numero. Intenta de nuevo\n" << endl;;
		}else if (x < 0) {
			cout << "El numero debe ser positivo. Intenta de nuevo\n" << endl;
		}
	}
	return x;
}

/** normalizeNumbers: Recive dos parametros enteros. 
	Se intercambian los valores si x es mayor a y
	para mantener esta regla. Esta funci�n retorna 
	una tupla ordenada d�nde la primer posici�n es 
	menor que la segunda.*/
tuple <int, int> normalizeNumbers (int x , int y){
	if (x > y){
		return make_tuple(y, x);
	}
	return make_tuple(x, y);
}

/** sumarMultiplos: Recive dos parametros enteros 
	que indican el intervalo para calcular los 
	multiplos de 5. Posteriormente suma todos 
	los multiplos calculados y los imprime en
	consola.
*/
void sumarMultiplos(int min, int max){
//	system("cls");
	int total = 0;
	for (int i = min; i <= max; i++){
		total += i*5;
	}
	cout << "\nLa suma de los multiplos de 5 entre " << min << " y " << max << " es: " << total << endl;
}

int main (){
	int a = 0, b = 0;
	cout << "Ingresa dos numeros positivos\n" << endl;
	a = positiveOnly("Numero 1: ");
	b = positiveOnly("Numero 2: "); 
	/*BUG: Al ingresar un letra como n�mero 1 el n�emerp 2 se queda en bucle*/
//	system("cls");
	
	cout << "Numeros ingresados: " << a << ", " << b << endl;
	tie(a,b) = normalizeNumbers(a,b);
	
	sumarMultiplos(a, b);
	return 0;
}
