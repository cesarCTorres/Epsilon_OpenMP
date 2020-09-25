/*
 ============================================================================
 Name        : Calculo_Epsilon_OpenMP.c
 Author      : Cesar Condori Torres
 Version     :
 Copyright   : Your copyright notice
 Description : Calculo del Valor de Epsilon
 Indicate number of Threads 'n' in Code:
 ============================================================================
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {  // declaramos la funcion principal

int n;
printf("\n Fuera de la región paralela, se utilizan 10 threads");
printf("\n \n Ingresa un valor para Iteraciones n : ");
scanf("%d",&n);   //Almacena el valor de la variable


omp_set_num_threads(10); // numero de hilos


double et = 0.0;   // variables
double tini, tfin, tiempo;  // variables
tini = omp_get_wtime(); // Tiempo inicio


#pragma omp parallel reduction(+:et) /// dentro de  la region paralela
{
int id = omp_get_thread_num();    // identificador de hilos
int nt = omp_get_num_threads();  // devuelve la cantidad de hilos.
double e=0;

int factorial(int f){  //declaramos el factorial
	int fact=f;
	if(fact>=1){
fact=f*factorial(f-1);
return fact;
}else{
return 1;
	}
}

for (int i=id; i<n; i+=nt){  // calculo del valor de epsilon
	double m = factorial(i);
	e+=1.0/m; //e=e+1.0/fact
	}	et+=e;

	tfin = omp_get_wtime();// fin del tiempo de ejecución
	tiempo = tfin - tini; // calculo del tiempo
}

printf("El valor de épsilon es: %.10f",et);   // mostramos los resultados
printf("\n Tiempo de ejecucion: %.8f\n", tiempo );
return 0;
}
