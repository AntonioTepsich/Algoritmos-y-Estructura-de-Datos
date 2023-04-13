#include <stdio.h>
#include <malloc.h>


typedef struct Nodo{
    int valor;
    struct Nodo* sig;
}Nodo;

typedef struct Cola{
    int tam;
    Nodo* cima;
}Cola;


void enqueue(Cola *cola, int data) {
    // Crear un nuevo nodo de cola
    Nodo* newNode = (Nodo*) malloc(sizeof(Nodo));

    if (newNode == NULL) {
        return NULL;
    }

    newNode->valor=data;
    newNode->sig=NULL;

    // Si la cola está vacía, el nuevo nodo es el frente y el final de la cola
    if (cola->tam==0) {
        cola->cima = newNode;
    } else {
        // Enlazar el nuevo nodo al final de la cola
        cola->cima->sig = newNode;
        cola->cima = newNode;
    }
    cola->tam+=1;
}

int dequeue(Cola* cola) {
    int res;
    Nodo* newNode = (Nodo*) malloc(sizeof(Nodo));

    if (newNode == NULL) {
        return NULL;
    }
    
    // Comprobar si la cola está vacía
    if (cola->tam == 0) {
        return NULL;
    } else {
        newNode=cola->cima;
        res = cola->cima->valor;
        cola->cima = newNode->sig;
        free(newNode);
        return res;
    }
}

void print_cola(Cola* cola) {
    printf("Los elementos de la cola son:\n");
    while (cola->cima != NULL) {
        printf("%d\n", cola->cima->valor);
        cola->cima = cola->cima->sig;
    }
}

