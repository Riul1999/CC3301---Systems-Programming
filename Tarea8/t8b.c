#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "viajante.h"

#include <setjmp.h>

//**RODRIGO URREA LOYOLA**
// los comentarios con **...** son los que yo he agregado
// **Esta metodologia podria no entregar el resultado correcto porque la rutina de atencion
// puede invocarse en cualquier momento del ciclo for, es decir se podria llamar justo al
// momento donde se haga la asignacion min=d y no se alcance a asignar los valores de z, por
// lo que podria haber una inconsistencia entre el minimo entregado y la supuesta ruta asociada.
// Una forma de corregir esto es llamar a sigprocmask antes de redefinir los nuevos minimos, es 
// decir luego del if (d<min).**

jmp_buf excp; //**definimos variable global para los jmp**
void advice(){ //**definimos la rutina de atencion**
  longjmp( excp, 1); //**decimos que vuelva al punto de retorno**
}

double viajante(int z[], int n, double **m, int nperm) {
  double min= DBL_MAX; // la distancia mas corta hasta el momento

  void(*hdlr)() = signal( SIGINT, advice); //**cambiamos la rutina de atencion y guardamos la anterior**
  if( setjmp(excp) == 0){ //**definimos el punto de retorno**
    for (int i= 1; i<=nperm; i++) {
      int x[n+1];          // almacenara una ruta aleatoria
      gen_ruta_alea(x, n); // genera ruta x[0]=0, x[1], x[2], ..., x[n], x[0]=0
      // calcula la distancia al recorrer 0, x[1], ..., x[n], 0
      double d= dist(x, n, m);
      if (d<min) {    // si distancia es menor a la mas corta hasta el momento
        min= d;       // d es la nueva distancia mas corta
        for (int j= 0; j<=n; j++)
          z[j]= x[j]; // guarda ruta mas corta en parametro z
    } } } else {}
  signal( SIGINT,hdlr); //**se restaura la rutina de atencion previa**
  return min;
}
