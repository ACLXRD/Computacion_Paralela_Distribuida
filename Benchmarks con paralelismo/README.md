# Benchmark utilizando multiplicación de matrices

- Autor 👨🏻‍💻: Andrés C. López R.
- Contacto 📧: andres.lopez01@correo.usa.edu.co

## Descripción
En este directorio se encunetran 3 interfaces (MM1c.c, MM1f.c  y MMPosix.c) y un modulo (modulo.c) con su respectivo archivo de cabecera (modulo.h). Cada interfaz realiza una multiplicación de matrices cuadradas usando el algoritmo clásico (fila x columna).

La característica principal de MM1c.c es que para realizar la multiplicación este inicia la multiplicación tomando la columna en primer lugar, mientras que MM1f.c toma la matriz transpuesta para iniciar por las filas. Por otra parte, MMPosix.c utiliza reserva de memoria e hilos para aprovechar el principio de  concurrencia y así tener más multiplicaciones de filas y columnas en simultáneo.

## Compilación:
> *Las siguientes instrucciones se realizan por consola o línea comandos.*

Para la compilación individual de cada módulo el proceso a seguir es el siguiente:

	gcc modulo.c -c
	gcc MM1c.c -c
	gcc modulo.o MM1c.o -o MM1c

Pero, para automatizar este proceso, se desarrolló un Makefile que realiza la compilación de las interfaces y los módulos de forma 	secuencial, agregando unas banderas que ayudan a la compilación correcta de cada programa. Para utilizar el Makefile se deben seguir los siguientes pasos:

	make clean  
> Elimina los ejecutables y los archivos .o  que existan en el directorio.
	
	make MM1c  
> Dependiendo de la interfaz que se quiera compilar, indicar el nombre de la misma, estos pueden ser: MM1c, MM1f o MMPosix

## Ejecución:
> Las siguientes instrucciones se realizan por consola o línea comandos.

Si se desea ejecutar uno de los programas previamente mencionados y compolados, se debe seguir los siguientes pasos:

	./MM1c N  
> Después del operado "./" debe ir el nombre del programa previamente compilado, estos pueden ser ./MM1c o ./MM1f La letra "N" hace referencia a un número entero positivo que equivale al tamaño de las matrices. Ej: ./MM1c 5

Si desea ver el tiempo de ejecución, del usuario, del sistema y el  total, escribir el siguiente comando:

	time ./MM1c N 
> La letra "N" hace referencia a un número entero positivo que equivale al tamaño de las matrices. Ej: time ./MM1c 5

Para la ejecución de MMPosix se deben ingresar dos parametros:

	./MMPosix N H 
> La letra "N" hace referencia a un número entero positivo que equivale al tamaño de las matrices. Ej: ./MMPosix 2000 2 

> La letra "H" hace referencia al número de hilos que se desea utilizar, este número debe ser menor al número de núcleos de procesamiento que posee el ordenador y además debe ser divisor del tamaño de la matriz. Ej ./MMPosix 4000 4

## Output
Después de la ejecución, el programa mostrará en consola el tiempo total que le tomo realizar únicamente la multiplicación. A continuación se muestra un ejemplo desde la compilación hasta el mensaje que se debe ver en consola.

	@user $: make clean
	rm -f  *.o
	rm -f MM1c MM1f MMPosix
	@user $: make MMPosix
	gcc  -pedantic -Wall modulo.c -c -lm -lpthread
	gcc  -pedantic -Wall MMPosix.c -c -lm -lpthread
	gcc  -pedantic -Wall modulo.o MMPosix.o -o MMPosix -lm -lpthread
	@user $: ./MMPosix 2000 8
	Total time: 15.762527 seg

