/*
 Autor: Andrés C. López
 Materia: Computación Paralela y Distribuida.
 Tema: Talle 1 en C++
 Descripción: Imprimir en pantalla un triangulo 
 en donde las líneas diagonales son secuncias 
 numéricas de 0 a 9.
*/

/* Declaración de interfaces: */
#include <iostream>
#include <cctype>


/*Declaración del espacio de dominio */
using namespace std;

/*Funciones*/

/*
	@breif: checkRange() verifica si un número está en un rango dado
	@param min: Limite inferior del rango
	@param max: Limite superior del rango
	@return Numero entero entre min y max.
*/
int checkRange(int min, int max){
	int x = 0;
	do{
		cout << "Ingrese un numero entre [11 - 20]: ";
		cin >> x;
	} while(x < 11 || x > 20);
	return x;
}	

int main (){
	int lineas = 0, aux = 0, c = 1;	
	lineas = checkRange(11, 20);
	
	/*
		Inicion del buble principal que controla el número de
		líneas del triangulo.
	*/
	for(int i = 1; i<= lineas; i++){ 
		/*
			En este bucle se toma el número mayor de cada línea
			este es el doble del anterior y además está en la 
			mitad de todos los números de cada línea.
		*/
		for (int j = i; j <= (i*2)-1 ; j++){ //digito
			c = j;			
		}
		/*
			Este bucle permite centrar el triagulo con espacios 
			a la izauierda. La líena final separa el centro del
			triangulo N donde N = lineas-1 siendo "lineas" la 
			cantidad de líneas del triangulo. 
		*/
		for (int l = lineas-i; l >= 0 ; l--){
			cout << " ";
		}
		/*
			En este bucle se imprime la parte izquierda del 
			triangulo, para mantener solo un digito se usa 
			%10 para extraer solo las unidades de los número 
			generados. La variable "k" toma el valor del 
			iterador "i" del bucle principal, ya que este
			es el primer valor de cada linea y se incrementá 
			hasta el valor de la variable c encontrada en el 
			bucle "digito".		
		*/
		for (int k = i; k < c ; k++){
			cout << k%10;
		} 
		/*
			En este bucle se imprime la aprte derecha del
			triangulo, para mantener solo un digito se usa 
			%10 para extraer solo las unidades de los número 
			generados. La variable "k" toma el valor de la 
			variable c encontrada en el bucle "digito" y se
			decrementa hasta el valor del iterador "i" del 
			bucle principal ya que este maraca el limite de
			la serie de cada línea.
		*/
		for (int k = c; k >= i ; k--){
			cout << k%10;
		}
		cout << "\n";
	}	
}

