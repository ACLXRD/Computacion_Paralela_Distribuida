/*
    Fecha: 10/02/2022
    Autor: Andrés C. López
    Materia: Computación Paralela y Distribuida.
    Tema: Programación de Funciones en C
    Descripción: Principal, puente entre interfaz y el módulo
*/

/* Se presenta la cabecera del módulo*/
#include "funciones.h" /*Se declara entre comillas ya que es una interfaz no estandar (en desarrollo)*/
#include <stdio.h>

int main (){
    int a = 10, b = 2, r = 0;
    
    printf("Programa principal\n");
    printf("Llamada a la funcion\n");
    r = sumar(a, b);
    printf("Resultado de la funcion: %d \n ", r);
    
    return 0;
}

/*
    Para la compilación se generan los objetos y posteriormente se enlazan
    gcc -Wall -c funciones.c 
    gcc -Wall -c main.c 
    gcc -Wall -o ejecutable funciones.o main.o
    ./ejecutable
*/
