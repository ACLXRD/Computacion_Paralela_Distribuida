/*
 Autor: Andrés C. López
 Materia: Computación Paralela y Distribuida.
 Tema: Talle 1 en C++
 Descripción: Sumar los números de su fecha de
 nacimiento y a continuación reduzcamos a un único
 dígito.
*/

/* Declaración de interfaces: */
#include <iostream>
#include <cctype>


/*Declaración del espacio de dominio */
using namespace std;

/*Funciones*/

/** getDay: Verificacion del día ingresado
	Retorna el día validado.
*/
int getDay (){
	int d = 0;
	while (d > 31 || d <= 0){
		cout << "\nDia: ";
		cin >> d;
		
		if (d > 31 || d <= 0){
			cout << "Numero invalido, intenta de nuevo." << endl;
		}
	}
	return d;
}

/** getMonth: Verificacion del mes ingresado
	Retorna el mes validado.
*/
int getMonth (){
	int m = 0;
	while (m > 12 || m <= 0){
		cout << "Mes: ";
		cin >> m;
		
		if (m > 12 || m <= 0){
			cout << "Numero invalido, intenta de nuevo." << endl;
		}
	}
	return m;
}

/** getYear: Verificacion del año ingresado
	Retorna el año validado.
*/
int getYear (){
	int y = 0;
	while (y > 2023 || y <= 0){
		cout << "Year: ";
		cin >> y;
		
		if (y > 2023 || y <= 0){
			cout << "Numero invalido, intenta de nuevo." << endl;
		}
	}
	return y;
}

/** calculateTarot: Calcula la suma de los digitos de un número.
	Parametro: La suma del día, mes y año de la fecha ingresada.
*/
void calculateTarot(int x){
	int digito, tarot;
	while(x != 0) {
        digito = x % 10;
        x /= 10;
        tarot += digito;
    }
    cout << "\nTu numero del tarot es " << tarot << endl;
}

int main (){
	int day = 0, month = 0 , year = 0;
	cout << "--- Numero del Tarot ---" << endl;
	cout << "\nIngresa tu fecha de nacimiento (dd/mm/yyyy)" << endl;
	
	/*Captura de datos con validación*/
	day = getDay();
	month = getMonth();
	year = getYear();
	cout << "Fecha de nacimiento ingresada --> " << day << "/" << month << "/" << year << endl;
	
	/*Calculo del número del taron*/
	calculateTarot(day+month+year);
	
	return 0;
}
