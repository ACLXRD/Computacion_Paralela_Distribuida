/*
 Autor: Andr�s C. L�pez
 Materia: Computaci�n Paralela y Distribuida.
 Tema: Talle 1 en C++
 Descripci�n: Se deben encontrar los centros num�ricos
 entre un intervalo dado
*/

/* Declaraci�n de interfaces: */
#include <iostream>
#include <cctype>

/*Declaraci�n del espacio de dominio */
using namespace std;

/*Funciones*/

/*
	@breif: checkNum() verifica que el n�mero ingresado sea 
	mayorl al limite indicado.
	@param min: Valor el cual, el n�mero ingresado debe ser mayor
	@return: N�mero validado mayor el @param min.
*/
int checkNum (int min){
	int x;
	do{
		cout << "Ingrese un numero mayor a " << min << ": ";
		cin >> x;	
		if(x <= 1){
			cout << "Valor invalido, intenta de nuevo\n" << endl;
		}
	}while(x <= 1);
	return x;
}

int main (){
	int n = checkNum(1);
	system("cls");
	cout << "Centros entre 1 y " << n << "\n" << endl;
	int sumaI = 0, sumaD = -1, centro = 1;
	/*
		Se inicializa sumaD en -1 para evitar que tome 
		a 1 como centro.
	*/
	do{
		/*
			sumaI suma los valores de izquiera al centro
			cada vez que el centro aumente esta suma tambien 
			aumenta.
		*/
		for (int i=1; i < centro; i++){
			sumaI += i;
		}
		/*
			sumaD suma los valores desde el centro hasta "n"
			pero avanzando uno a uno. Si sumaI == sumaD, se 
			interrumpe el ciclo, las sumas se reinician y el
			centro aumenta hasta que el centro llegue a "n"
		*/
		for(int j = centro+1; j <= n; j++ ){
			if(sumaI == sumaD){
				cout << "Centro en " << centro << endl;
				break;
			}else{
				sumaD += j;
			}
		}
		centro++;
		sumaI = 0;
		sumaD = 0;
	}while (centro <= n);	
}
