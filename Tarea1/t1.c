#include <stdio.h>
#include <stdlib.h>

#include "t1.h"

unsigned long long dupMasLargo(unsigned long long x) {
    unsigned long long duplicado=0;
    for (int i = 1 ; i <= 32 ;  i++){
        unsigned long long sec = (x << (64 - i)) >> (64 - i);
        unsigned long long secuencia = sec + (sec<<i);
        unsigned long long prueba = (x << (64 - i-i)) >> (64 - i-i);
        if (prueba == secuencia) {
            unsigned long long tamano = i;
            tamano <<= 32; 
            duplicado = sec + tamano;
        }
    }
    return duplicado;
}