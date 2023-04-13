#include <stdio.h>
#include <stdlib.h>

/*
Ejercicio 5.1
    1-2-Para eliminar el ultimo elemento de una lista simplemente
    enlazada con complejidad O(1) pondria el puntero ultimmo en el ante ultimo elemento
    asi lograria eliminar el que sigue sin tener que recorrer toda la lista.
*/

/*
Ejercicio 5.2
    Implementar una función que permita verificar si una lista es
    un palíndromo (es decir, los elementos son los mismos cuando se lee de principio a fin o al
    revés). No se pueden usar estructuras de datos adicionales para resolver este problema.
*/



typedef struct nodo{
	int dato;
	struct nodo* siguiente;
} nodo;

typedef struct listas
{
    int tam;
    nodo* cabeza;
}listas;



listas* crearLista();
void imprimir(listas*);
void insertarNodoPrincipio(listas*,int);
void removerPrincipio(listas* );
nodo* buscarNodo(listas* ,int);

int main(){
    listas* lista=crearLista();
    insertarNodoPrincipio(lista,25);
    insertarNodoPrincipio(lista,15);
    insertarNodoPrincipio(lista,10);

    imprimir(lista);
    
    return 0;
}

void imprimir(listas* lista){
    nodo* actual= lista->cabeza;

    while (actual!=NULL){
        printf("Valor: %d",actual->dato);
        actual=actual->siguiente;
    }
}

listas* crearLista(){
    listas* lista=(listas*)malloc(sizeof(listas));
    lista->tam=0;
    lista->cabeza=NULL;
    return lista;
}

void insertarNodoPrincipio(listas* lista,int valor){
	nodo* nuevo = (nodo*) malloc(sizeof(nodo));
	nuevo->dato=valor;
	if(lista->tam==0){
		lista->cabeza = nuevo;
		nuevo->siguiente = NULL;
	}else{
        nodo* cabeza_vieja=lista->cabeza;
        lista->cabeza=nuevo;
		nuevo->siguiente =cabeza_vieja;
	}
    lista->tam++;
	printf("\n Nodo ingresado con Exito al inicio\n\n");
}

void removerPrincipio(listas* lista){
    int tam=lista->tam;
    if(tam>0){
        nodo* cabeza_vieja= lista->cabeza;
        lista->cabeza=cabeza_vieja->siguiente;
        free(cabeza_vieja);
        lista->tam--;
    }
}

nodo* buscarNodo(listas* lista,int valor){
    nodo* actual=lista->cabeza;
    while (actual!=NULL){
        if(actual->dato==valor){
            break;
        }
        else{
            actual=actual->siguiente;
        }
    }
    return actual;
}

 