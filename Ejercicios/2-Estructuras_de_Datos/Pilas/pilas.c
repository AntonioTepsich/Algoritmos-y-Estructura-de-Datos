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
    if(pila==NULL){ return NULL;}
    pila->tam=0;
    pila->cima=NULL;
    return pila;
}

void push(Pila* pila,int valor){
    Nodo* newNode=(Nodo*)malloc(sizeof(Nodo));
    if(newNode==NULL){ return NULL;}

    newNode->valor=valor;

    if(pila->tam==0){
        newNode->sig=NULL;
        pila->cima=newNode;
    }
    else{
        newNode->sig=pila->cima;
        pila->cima=newNode;
    }
    pila->tam+=1;
}

void* pop(Pila* pila){
    Nodo* aux;
    int res;

    if(pila->tam==0){
        return NULL; 
    } else{
        aux=pila->cima;
        res=pila->cima->valor;
        pila->cima=aux->sig;
        free(aux);
        return res;
    }
}

void* peak(Pila* pila){
    return pila->cima->valor;
}

void print_Pila(Pila* pila) {
    printf("Los elementos de la pila son:\n");
    while (pila->cima != NULL) {
        printf("%d\n", pila->cima->valor);
        pila->cima= pila->cima->sig;
    }
}
