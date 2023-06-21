#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INIT 20       //TAMAÑO INICIAL DEL DICCIONARIO


//estructura de una lista simplemente enlazada
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

Lista* crearLista(){
    Lista *lista=(Lista*)malloc(sizeof(Lista));
    if(lista==NULL){
      return NULL;
    }
    lista->size=0;
    lista->head=NULL;
    return lista;
}

bool insertarNodoPrincipio(Lista* lista,const char* key,void *valor){
	Node* nuevo = (Node*) malloc(sizeof(Node));
	if(nuevo==NULL){
    return false;
  }
  nuevo->key=(char*)malloc(strlen(key)+1);
  if(nuevo->key==NULL){
    free(nuevo);
    return false;
  }

  strcpy(nuevo->key,key);
  nuevo->value=valor;
	if(lista->size==0){
		lista->head = nuevo;
		nuevo->next = NULL;
	}else{
    Node* cabeza_vieja=lista->head;
    lista->head=nuevo;
		nuevo->next =cabeza_vieja;
	}
  lista->size++;
  return true;
}
void* removerPrincipio(Lista* lista){
    size_t tam=lista->size;
    if(tam>0){
      Node* cabeza_vieja = lista->head;
      
      lista->head=cabeza_vieja->next;

      void* valor=cabeza_vieja->value;
      free(cabeza_vieja->key);
      free(cabeza_vieja);
      lista->size--;
      return valor;
    }
    return false;
}

Node* buscarNodo(Lista* lista,const char* key){  //puede fallar
    Node* actual=lista->head;
    int encuentra = 0;
    while (actual!=NULL){
        if(strcmp(actual->key,key)==0){
          encuentra=1;
          break;
        }
        else{
          actual=actual->next;
        }
    }
    if(encuentra==0){
      return NULL;
    }
    return actual;
}

dictionary_t *dictionary_create(destroy_f destroy) {
  dictionary_t* diccionario = (dictionary_t*)malloc(sizeof(dictionary_t));
  if (diccionario == NULL) {
    return NULL;
  }

  diccionario->listas = (Lista*)malloc(sizeof(Lista) * INIT);
  if (diccionario->listas == NULL) {
    free(diccionario);
    return NULL;
  }

  for (int i = 0; i < INIT; i++) {
    Lista* lista = crearLista();
    if (lista == NULL) {
      // Liberar recursos asignados previamente
      for (int j = 0; j < i; j++) {
        Node* nodo = diccionario->listas[j].head;
        while (nodo != NULL) {
          Node* siguiente = nodo->next;
          free(nodo->key);
          if (diccionario->destroy != NULL) {
            diccionario->destroy(nodo->value);
          }
          free(nodo);
          nodo = siguiente;
        }
      }
      free(diccionario->listas);
      free(diccionario);
      return NULL;
    }
    diccionario->listas[i] = *lista;
    free(lista);
  }

  diccionario->size = 0;
  diccionario->capacity = INIT;
  diccionario->destroy = destroy;
  return diccionario;
};

size_t hash_function(const char *key, size_t capacity) {
  size_t hash = 0;
  size_t lenght = strlen(key);
  for (size_t i = 0; i<lenght; i++) {
    hash += key[i];
    hash = (hash * key[i]);
  }
  return hash%capacity;
};


// dictionary_t* re_hash(dictionary_t* dictionary, size_t capacity) {
//   Lista* nuevasListas = (Lista*)malloc(sizeof(Lista) * capacity);
//   if (nuevasListas == NULL) {
//     return NULL;
//   }

//   for (size_t i = 0; i < capacity; i++) {
//     nuevasListas[i].head = NULL;
//     nuevasListas[i].size = 0;
//   }

//   for (size_t i = 0; i < dictionary->capacity; i++) {
//     Node* nodo = dictionary->listas[i].head;
//     while (nodo != NULL) {
//       size_t index = hash_function(nodo->key, capacity);
//       Node* siguiente = nodo->next;
//       nodo->next = nuevasListas[index].head;
//       nuevasListas[index].head = nodo;
//       nuevasListas[index].size++;

//       nodo = siguiente;
//     }
//   }

//   for (size_t i = 0; i < dictionary->capacity; i++) {
//     Node* nodo = dictionary->listas[i].head;
//     while (nodo != NULL) {
//       Node* siguiente = nodo->next;
//       free(nodo->key);
//       if (dictionary->destroy != NULL) {
//         dictionary->destroy(nodo->value);
//       }
//       free(nodo);
//       nodo = siguiente;
//     }
//   }

//   free(dictionary->listas);
//   dictionary->listas = nuevasListas;
//   dictionary->capacity = capacity;

//   return dictionary;
// };

dictionary_t* re_hash(dictionary_t* dictionary, size_t capacity) {
  Lista* nuevasListas = (Lista*)malloc(sizeof(Lista) * capacity);
  if (nuevasListas == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < capacity; i++) {
    nuevasListas[i].head = NULL;
    nuevasListas[i].size = 0;
  }

  for (size_t i = 0; i < dictionary->capacity; i++){
    Node* nodo = dictionary->listas[i].head;
    while (nodo){
      Node* siguiente = nodo->next;
      size_t index = hash_function(nodo->key, capacity);
      if(!nuevasListas[index].head){
        nodo->next = NULL;
      }
      else{
        nodo->next = nuevasListas[index].head;
      }
      nuevasListas[index].head = nodo;
      nuevasListas[index].size++;

      nodo = siguiente;
    }
  }

  free(dictionary->listas);
  dictionary->listas = nuevasListas;
  dictionary->capacity = capacity;

  return dictionary;
}


bool dictionary_put(dictionary_t *dictionary, const char *key, void *value) {

  if (dictionary->size >= (double)(dictionary->capacity) * 0.7) {
    dictionary_t* diccionario_nuevo=re_hash(dictionary,dictionary->capacity*2);
    if(diccionario_nuevo==NULL){
      return false;
    }
    dictionary=diccionario_nuevo;
  }

  size_t index = hash_function(key, dictionary->capacity);
  if(dictionary->listas[index].size==0){
    bool a=false;
    a=insertarNodoPrincipio(&dictionary->listas[index],key,value);
    if(a==false){
      return false;
    }
    dictionary->size++;
    return true;
  }else{
    Node* nodo=dictionary->listas[index].head;
    while(nodo!=NULL){                              
      if(strcmp(nodo->key,key)==0){
        if(dictionary->destroy!=NULL){
          dictionary->destroy(nodo->value);
        }
        nodo->value=value;
        return true;
      }
      nodo=nodo->next;
    }
    bool a=false;
    a=insertarNodoPrincipio(&dictionary->listas[index],key,value);
    if(a==false){
      return false;
    }
    dictionary->size++;
    return true;
  }
};

void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
  size_t index = hash_function(key, dictionary->capacity);
  Node* nodo=dictionary->listas[index].head;
  while(nodo!=NULL){
    if(strcmp(nodo->key,key)==0){
      *err=false;
      return nodo->value;
    }
    nodo=nodo->next;
  }
  *err=true;
  return NULL;
};

bool dictionary_delete(dictionary_t *dictionary, const char *key) {
  size_t index = hash_function(key, dictionary->capacity);
  Node* nodo=dictionary->listas[index].head;
  Node* nodo_sig=nodo->next;

  if(nodo==NULL) {
      return false;
   } 
  if(strcmp(nodo->key,key)==0){
    void* a;
    if(dictionary->destroy!=NULL){
      dictionary->destroy(nodo->value);
    }
    a=removerPrincipio(&dictionary->listas[index]);
    if(a==NULL){
      return false;
    }
    dictionary->size--;
    return true;
  }
  else if(strcmp(nodo->key,key)!=0 && nodo->next == NULL) {
      return false;
  }
  else {
      while(nodo_sig!=NULL) {
         if(strcmp(nodo_sig->key,key)==0) {
            nodo->next = nodo_sig->next;  
            dictionary->listas[index].size--;
            if(dictionary->destroy != NULL){
              dictionary->destroy(nodo_sig->value);
            }
            free(nodo_sig->key);
            free(nodo_sig);
            dictionary->size--;
            return true;
         }
         nodo = nodo->next;
         nodo_sig = nodo_sig->next;
      }
      return false;
   }
};

void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err) {
  size_t index = hash_function(key, dictionary->capacity);
  Node* nodo = dictionary->listas[index].head;
  if (nodo == NULL) {
    *err = true;
    return NULL;
  } 
  if (strcmp(nodo->key, key) == 0) {
    void* a = removerPrincipio(&dictionary->listas[index]);
    if (a == NULL) {
      *err = true;
      return NULL;
    }
    dictionary->size--;
    *err = false;
    return a;
  } 
  if(nodo->next == NULL) {
    *err = true;
    return NULL;
  }
  Node* nodo_sig = nodo->next;
  
    while (nodo_sig != NULL) {
      if (strcmp(nodo_sig->key, key) == 0) {
        dictionary->size--;
        dictionary->listas[index].size--;
        nodo->next = nodo_sig->next;
        void* value = nodo_sig->value;
        if(dictionary->destroy != NULL){
          dictionary->destroy(nodo_sig->value);
        }
        free(nodo_sig->key);
        free(nodo_sig);     // liberar bien todo
        *err = false;
        return value;
      }
      nodo = nodo->next;
      nodo_sig = nodo_sig->next;
    }
    *err = true;
    return NULL;
}


bool dictionary_contains(dictionary_t *dictionary, const char *key) {
  size_t index = hash_function(key, dictionary->capacity);
  Node* nodo=dictionary->listas[index].head;
  while(nodo!=NULL){
    if(strcmp(nodo->key,key)==0){
      return true;
    }
    nodo=nodo->next;
  }
  return false;
};

size_t dictionary_size(dictionary_t *dictionary) { 
  return dictionary->size; 
};

void dictionary_destroy(dictionary_t *dictionary){
  for (size_t i = 0; i < dictionary->capacity; i++) {
    Node *nodo = dictionary->listas[i].head;
    while (nodo != NULL) {
      Node *siguiente = nodo->next;
      free(nodo->key);  
      if (dictionary->destroy != NULL) {
        dictionary->destroy(nodo->value);
      }
      free(nodo);
      nodo = siguiente;
    }
  }
  free(dictionary->listas);
  free(dictionary);
};
