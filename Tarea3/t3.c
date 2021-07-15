#include "t3.h"
#include "stdio.h"
#include "stdlib.h"


void desbalancear(Nodo **pa, Nodo **pult) {
    if (*pa == NULL) {
        *pult = NULL;
        return;
    }
    Nodo *arbol = *pa;
    *pult = arbol;
    if (arbol->izq == NULL) {
        if (arbol->der != NULL) {
            desbalancear(&(arbol->der),pult);
        }
        return;
    }
    desbalancear(&(arbol->izq),pult);
    *pa = arbol->izq;
    arbol->izq = NULL;
    (*pult)->der = arbol;
    *pult = arbol;
    if (arbol->der != NULL) {
            desbalancear(&(arbol->der),pult);
    }
    return;
}

Nodo *desbalanceado(Nodo *a, Nodo **pult){
    if (a == NULL) {
        *pult = NULL;
        return NULL;
    }
    Nodo * respuesta = malloc(sizeof(Nodo));
    respuesta->id = a->id;
    respuesta->hash = a->hash;
    respuesta->izq = NULL;
    *pult = respuesta;
    if (a->izq == NULL) {
        if (a->der != NULL) {
            respuesta->der = desbalanceado(a->der,pult);
        }else {
            respuesta->der = NULL;
        }
        return respuesta;
    }
    Nodo *primero = desbalanceado(a->izq,pult);
    Nodo *ultimo = *pult;
    *pult = respuesta;
    ultimo->der = respuesta;
    if (a->der != NULL) {
            respuesta->der = desbalanceado(a->der,pult);
    }else {
            respuesta->der = NULL;
    }
    return primero;
}