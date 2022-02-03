/*Fecha: 1/02/2022
* Autor: Andrés C. López
* Materia: Computación Paralela y Distribuida.
* Tema: Tipos de datos
* Descripción: Aplicación para observar el tamaño de los tipos de datos.
*/

/* Declaración de interfaces: */
#include <iostream>

/*Declaración del espacio de dominio */
using namespace std;

/*Definición de constantes*/
#define SIZEBITES(x) sizeof(x) * 8 /*Función lambda para calculo de bites*/

int main(){
	cout << "=========================================================================================" << endl;
	cout << "|	Type		|	Meaning			| 	Bytes	|     bite	|" << endl;
	cout << "=========================================================================================" << endl;
	cout << "|	bool		|	Boleano			|	 " 	<<sizeof(bool) <<"	|	  "<<	SIZEBITES(bool)	<<"	|" << endl;
	cout << "|	char		|	Character		|	 " 	<<sizeof(char) <<"	|	  "<<	SIZEBITES(char)	<<"	|" << endl;
	cout << "|	wchar_t		|	Wide Character		|	 "	 <<sizeof(wchar_t) <<"	|	 "<<	SIZEBITES(wchar_t)	<<"	|" << endl;
	cout << "|	char16_t	|	Unicode Character	|	 " <<sizeof(char16_t) <<"	|	 "<<	SIZEBITES(char16_t)	<<"	|" << endl;
	cout << "|	char32_t	|	Unicode Character	|	 " <<sizeof(char32_t) <<"	|	 "<<	SIZEBITES(char32_t)	<<"	|" << endl;
	cout << "|	short		|	Short Integer		|	 " 	<<sizeof(short) <<"	|	 "<<	SIZEBITES(short)	<<"	|" << endl;
	cout << "|	int		|	Integer			|	 " 	<<sizeof(int) <<"	|	 "	<<	SIZEBITES(int)	<<"	|" << endl;
	cout << "|	long		|	Long Integer		|	 " 	<<sizeof(long) <<"	|	 "	<<	SIZEBITES(long)	<<"	|" << endl;
	cout << "|	long long	|	Long Long  Integer	|	 " 	<<sizeof(long long) <<"	|	 "	<<	SIZEBITES(long long)	<<"	|" << endl;
	cout << "|	float		|Single Precision Floating Point|	 "	 <<sizeof(float) <<"	| 	 "	<<	SIZEBITES(float)	<<"	|" << endl;
	cout << "|	double		|Double Precision Floating Point|	 " <<sizeof(double) <<"	|	 "	<<	SIZEBITES(double)	<<"	|" << endl;
	cout << "|	long double	|Extend Precision Floating Point|	" <<sizeof(long double) <<"	|	"	<<	SIZEBITES(long double)	<<"	|" << endl;	
	cout << "=========================================================================================" << endl;
return 0;
}
