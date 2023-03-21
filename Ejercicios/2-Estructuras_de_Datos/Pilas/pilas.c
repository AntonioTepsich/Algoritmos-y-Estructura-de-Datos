#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
    int valor;
    struct Nodo* sig;
}Nodo;

typedef struct Pila{
    int tam;
    Nodo* cima;
}Pila;

Pila* crearPila();
void push(Pila*,int);

int main(){
    Pila* pila=crearPila();

    return 0;
}

Pila* crearPila(){
    Pila* pila= (Pila*) malloc(sizeof(Pila));
    pila->tam=0;
    pila->cima=NULL;
    return pila;
}

void push(Pila* pila,int valor){
    Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
    nuevo->valor=valor;
    if(pila->tam==0){
        nuevo->sig=NULL;
        pila->cima=nuevo;
    }
    else{
        nuevo->sig=pila->cima;
        pila->cima=nuevo;
    }
    pila->tam=pila->tam+1;
}