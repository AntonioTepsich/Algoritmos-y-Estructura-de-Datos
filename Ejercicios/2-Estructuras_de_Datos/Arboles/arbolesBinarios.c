#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Nodo{
    int dato;
    int hijosDer,hijosIzq;
    struct Nodo *padre ,*izq,*der;
}Nodo;

typedef struct arbolB{
    int totalIzq,totalDer;
    Nodo* raiz;
}arbolB;


arbolB* CrearArbol(){
    arbolB* a = (arbolB*)malloc(sizeof(arbolB));
    a->totalIzq=0;
    a->totalDer=0;
    a->raiz=NULL;
    return a;
}

Nodo* crearNodo(int dato){
    Nodo* a = (Nodo*)malloc(sizeof(Nodo));
    a->der=NULL;
    a->izq=NULL;
    a->padre=NULL;
    a->dato=dato;
    a->hijosDer=0;
    a->hijosIzq=0;
    return a;
}

int estaVacio(arbolB* a){
    int b;
    (a->raiz==NULL) ? (b=1) : (b=0);
    return b;
}

