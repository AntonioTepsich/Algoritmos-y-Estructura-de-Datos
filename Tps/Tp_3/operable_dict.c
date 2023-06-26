#include <stdbool.h>
#include "operable_dict.h"
/*
 * Punto extra de operable dict, suma 3 puntos como máximo.
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
 * Inserta o pisa en dictionary1 todas las claves y valores que están en dictionary2.
 * Las claves se mantienen independientes entre ambos diccionarios, pero los valores no.
 * (las claves nuevas de agregar dictionary2 en dictionary1 deben ser punteros distintos
 * pero los valores son el mismo puntero).
 * La operación es atómica, si falla dictionary1 queda en el mismo estado que estaba antes del update.
 * Devuelve true si funcionó, false si fayó.
 */


bool dictionary_update(dictionary_t *dictionary1, dictionary_t *dictionary2){
    dictionary_t *dicAux=dictionary1;
    for(size_t i=0;i<dictionary2->capacity;i++){
        Node* nodo=dictionary2->listas[i].head;
        while(nodo!=NULL){
                if(dictionary_put(dictionary1,nodo->key,nodo->value)){
                    dictionary1=dicAux;
                    return false;
                }
            nodo=nodo->next;
        }
    }
    return true;
}

/*
 * Combina ambos diccionarios en uno nuevo que contiene solo las claves que están presentes en ambos.
 * En todos los casos se conservan los valores del dictionary1.
 * Devuelve NULL si falla.
 */
dictionary_t* dictionary_and(dictionary_t *dictionary1, dictionary_t *dictionary2){
    dictionary_t *dictionary3=dictionary_create(dictionary1->destroy);
    if(dictionary3==NULL){
      return NULL;
    }

    for(size_t i=0;i<dictionary1->capacity;i++){
      Node* nodo=dictionary1->listas[i].head;
      while(nodo!=NULL){
        if(dictionary_contains(dictionary2,nodo->key)){
          if(dictionary_put(dictionary3,nodo->key,nodo->value)){
            return NULL;
          }
        }
        nodo=nodo->next;
      }
    }
    return dictionary3;
    return NULL;
}

/*
 * Combina ambos diccionarios en uno nuevo que contiene todas las claves de ambos.
 * En caso de que ambos tengan una misma clave se conserva el valor de dictionary1.
 * Devuelve NULL si falla.
 */
dictionary_t* dictionary_or(dictionary_t *dictionary1, dictionary_t *dictionary2){
    dictionary_t *dictionary3=dictionary_create(dictionary1->destroy);
    if(dictionary3==NULL){
      return NULL;
    }

    for(size_t i=0;i<dictionary2->capacity;i++){
      Node* nodo=dictionary2->listas[i].head;
      while(nodo!=NULL){
        if(dictionary_put(dictionary3,nodo->key,nodo->value)){
          return NULL;
        }
        nodo=nodo->next;
      }
    }
    for(size_t i=0;i<dictionary1->capacity;i++){
      Node* nodo=dictionary1->listas[i].head;
      while(nodo!=NULL){
        if(dictionary_put(dictionary3,nodo->key,nodo->value)){
          return NULL;
        }
        nodo=nodo->next;
      }
    }
    return dictionary3;
    return NULL;
}

/*
 * Devuelve true si ambos diccionarios son iguales. Dos diccionarios son iguales sí:
 *  - Las claves son iguales aunque puedan tener distinta posición en memoria.
 *  - Los values son los mismos punteros para cada clave
 *  - Tienen la misma cantidad de claves
 */
bool dictionary_equals(dictionary_t *dictionary1, dictionary_t *dictionary2){
    if(dictionary1->size!=dictionary2->size){
      return false;
    }
    for(size_t i=0;i<dictionary1->capacity;i++){
      Node* nodo=dictionary1->listas[i].head;
      while(nodo!=NULL){
        if(!dictionary_contains(dictionary2,nodo->key)){
          return false;
        }
        bool err=true;
        void *value2=dictionary_get(dictionary2,nodo->key,&err);
        if(err){
          return false;
        }
        if(value2!=nodo->value){
          return false;
        }
        nodo=nodo->next;
      }
    }
    return true;
    
}
