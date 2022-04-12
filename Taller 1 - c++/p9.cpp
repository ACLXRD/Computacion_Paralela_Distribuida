/*
 Autor: Andr�s C. L�pez
 Materia: Computaci�n Paralela y Distribuida.
 Tema: Talle 1 en C++
 Descripci�n: Imprimir en pantalla un triangulo 
 en donde las l�neas diagonales son secuncias 
 num�ricas de 0 a 9.
*/

/* Declaraci�n de interfaces: */
#include <iostream>
#include <cctype>


/*Declaraci�n del espacio de dominio */
using namespace std;

/*Funciones*/

/*
	@breif: checkRange() verifica si un n�mero est� en un rango dado
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
		Inicion del buble principal que controla el n�mero de
		l�neas del triangulo.
	*/
	for(int i = 1; i<= lineas; i++){ 
		/*
			En este bucle se toma el n�mero mayor de cada l�nea
			este es el doble del anterior y adem�s est� en la 
			mitad de todos los n�meros de cada l�nea.
		*/
		for (int j = i; j <= (i*2)-1 ; j++){ //digito
			c = j;			
		}
		/*
			Este bucle permite centrar el triagulo con espacios 
			a la izauierda. La l�ena final separa el centro del
			triangulo N donde N = lineas-1 siendo "lineas" la 
			cantidad de l�neas del triangulo. 
		*/
		for (int l = lineas-i; l >= 0 ; l--){
			cout << " ";
		}
		/*
			En este bucle se imprime la parte izquierda del 
			triangulo, para mantener solo un digito se usa 
			%10 para extraer solo las unidades de los n�mero 
			generados. La variable "k" toma el valor del 
			iterador "i" del bucle principal, ya que este
			es el primer valor de cada linea y se increment� 
			hasta el valor de la variable c encontrada en el 
			bucle "digito".		
		*/
		for (int k = i; k < c ; k++){
			cout << k%10;
		} 
		/*
			En este bucle se imprime la aprte derecha del
			triangulo, para mantener solo un digito se usa 
			%10 para extraer solo las unidades de los n�mero 
			generados. La variable "k" toma el valor de la 
			variable c encontrada en el bucle "digito" y se
			decrementa hasta el valor del iterador "i" del 
			bucle principal ya que este maraca el limite de
			la serie de cada l�nea.
		*/
		for (int k = c; k >= i ; k--){
			cout << k%10;
		}
		cout << "\n";
	}	
}

