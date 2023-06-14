#include "internal_iterator.h"

/*
 * Punto extra de internal iterator, suma 1 punto como máximo.
 */
typedef struct node {
  char *key;
  void *value;
  struct node *next;
} Node;

typedef struct lista {
  Node *head;
  size_t size;
} Lista;


struct dictionary {
  Lista *listas;
  size_t size;
  size_t capacity;
  destroy_f destroy;
};


/*
 * Itera cada par clave-valor del diccionario pasandoselo a la función de iteración.
 * Recibe un parámetro extra que puede contener cualquier cosa para permitirle a la función guardar resultados.
 */
void iterate(dictionary_t* dict, iterate_f f, void* extra){
    for(size_t i=0;i<dict->capacity;i++){
        Node* nodo=dict->listas[i].head;
        while(nodo!=NULL){
            if(f(nodo->key,nodo->value,extra)){
            return;
            }
            nodo=nodo->next;
        }
    }
    return;
}
