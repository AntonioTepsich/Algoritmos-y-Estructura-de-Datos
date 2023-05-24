#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INIT 20       //TAMAÑO INICIAL DEL DICCIONARIO

/*
char SortedArray[10];
bool isShort;
char* long_str;
*/

typedef struct Item{
  char *key;
  void *value;
  bool deleted;
}Item;

struct dictionary {
  Item *items;
  size_t size;
  size_t capacity;
  destroy_f destroy;
};

Item *item_create(const char *key, void *value) {
  Item *item = (Item*)malloc(sizeof(Item));
  if (item == NULL) {
    return NULL;
  }
  item->key = (char*)malloc(strlen(key)+1);
  if (item->key == NULL) {
    free(item);
    return NULL;
  }
  strcpy(item->key, key);
  item->value = value;
  item->deleted = false;
  return item;
};

dictionary_t *dictionary_create(destroy_f destroy) {
  dictionary_t *dictionary = (dictionary_t*)malloc(sizeof(dictionary_t));
  if (dictionary == NULL) {
    return NULL;
  }
  for(int i = 0; i < INIT; i++){
    Item* item=item_create(NULL,NULL);
    if (item == NULL) {
      free(dictionary);
      return NULL;
    }
    dictionary->items[i]=*item;
  }
  dictionary->size = 0;
  dictionary->capacity = INIT;
  dictionary->destroy = destroy;
  return dictionary;
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

bool handle_collision(dictionary_t *dictionary, size_t index, Item *item){
  /*
  | x|
  | |
  | x| -
  | x|
  mod tamaño tabla
  */
  for (size_t i = index; i<dictionary->size; i++){
    if(dictionary->items[i].key==item->key){
      dictionary->items[i].value = item->value;
      return true;
    }
    if (dictionary->items[i].key == NULL){
      dictionary->items[i].deleted = false;
      dictionary->items[i].key = item->key;
      dictionary->items[i].value = item->value;
      dictionary->size++;
      return true;
    }
  }
  for (size_t i = 0; i < index; i++) {
    if(dictionary->items[i].key==item->key){
      dictionary->items[i].value = item->value;
      return true;
    }
    if (dictionary->items[i].key == NULL){
      dictionary->items[i].deleted = false;
      dictionary->items[i].key = item->key;
      dictionary->items[i].value = item->value;
      dictionary->size++;
      return true;
    }
  } 
  return false;
};

dictionary_t *dictionary_create2(size_t capacity, destroy_f destroy) {
  dictionary_t *dictionary = (dictionary_t*)malloc(sizeof(dictionary_t));
  if (dictionary == NULL) {
    return NULL;
  }
  dictionary->items = (Item*)malloc(capacity*sizeof(Item));
  if (dictionary->items == NULL) {
    free(dictionary);
    return NULL;
  }
  for(int i = 0; i < capacity; i++){
    dictionary->items[i].key = NULL;
    dictionary->items[i].value = NULL;
    dictionary->items[i].deleted = false;
  }
  dictionary->size = 0;
  dictionary->capacity = capacity;
  dictionary->destroy = destroy;
  return dictionary;
 };

dictionary_t* re_hash(dictionary_t* dictionary, size_t capacity) {
  dictionary_t *dictionary2 = dictionary_create2(capacity,dictionary->destroy);
  if (dictionary2 == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < dictionary->capacity; i++) {
    if (dictionary->items[i].key != NULL) {
      dictionary_put(dictionary2, dictionary->items[i].key, dictionary->items[i].value);
    }
  }
  //dictionary_destroy(dictionary);
  return dictionary2;
};

/*
Fijarse Key si ya esta.
Si: Borrar value anterior y poner el nuevo.
No: Hay colision? Agregar key y value.
*/

bool dictionary_put(dictionary_t *dictionary, const char *key, void *value) {
  size_t cap = dictionary->capacity;
  double b = 0.6;
  size_t a = (size_t)((int)cap*b);
  int c = 2;
  size_t d = (size_t)((int)cap*c);

  if(dictionary->size >= a){
    printf("---------------Rehashea\n");
    dictionary = re_hash(dictionary, d);
    if(dictionary == NULL){
      printf("---------------Error al rehashear\n");
      return false;
    }
  }
  Item *item = (Item*)malloc(sizeof(Item));
  if (item == NULL) {
    return false;
  }
  size_t index = hash_function(key, dictionary->capacity);

  // item->key = (char*)malloc(sizeof(key)/sizeof(*key));
  // if (item->key == NULL) {
  //   free(item);
  //   return false;
  // }
  item->key = malloc(strlen(key)+1);
  if (item->key == NULL) {
    free(item);
    return false;
  }
  strcpy(item->key, key);
  item->value = value;
  item->deleted = false;
  if(dictionary->items[index].key == NULL){
    dictionary->items[index] = *item;
    dictionary->size+=1;
    return true;
  }
  handle_collision(dictionary,index,item); //VER SI ESTA BIEN
  
  if(dictionary == NULL){
    free(item);
    return false;
  }
  dictionary->items[index] = *item;
  // dictionary->size+=1;
  return true;
};

void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
  size_t index = hash_function(key, dictionary->capacity);
  if (dictionary->items[index].key == NULL && dictionary->items[index].deleted == false) {
    *err = true;
    return NULL;
  }
  if (strcmp(dictionary->items[index].key, key) == 0) {
    *err = false;
    return dictionary->items[index].value;
  
  }
  for(size_t i=index; i<dictionary->size; i++){
    if(dictionary->items[i].key == NULL && dictionary->items[i].deleted == false){
      *err = true;
      return NULL;
    }
    if(strcmp(dictionary->items[i].key, key) == 0) {
      *err = false;
      // puts("ACAAA\n");
      // printf("%p\n",dictionary->items[i].value);
      return dictionary->items[i].value;
    }
  }
  for(size_t i=0; i<index; i++){
    if(dictionary->items[i].key == NULL && dictionary->items[i].deleted == false){
      *err = true;
      return NULL;
    }
    if(strcmp(dictionary->items[i].key, key) == 0) {
      *err = false;
      return dictionary->items[i].value;
    }
  }
  *err = true;
  return NULL;
};

bool dictionary_delete(dictionary_t *dictionary, const char *key) {
  bool err=false;
  dictionary_pop(dictionary, key, &err);
  if(err == false){
    return true;
  }
  return false;
};

void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err) {
  if (!dictionary_contains(dictionary, key)) {
    *err = true;
    return NULL;
  }

  size_t index = hash_function(key, dictionary->capacity);
  for (size_t i = index; i < dictionary->capacity; i++) {
    if (dictionary->items[i].key != NULL && strcmp(dictionary->items[i].key, key) == 0 && !dictionary->items[i].deleted) {
      void *value = dictionary->items[i].value;
      // free(dictionary->items[i].key);
      dictionary->items[i].key = NULL;
      dictionary->items[i].value = NULL;
      dictionary->items[i].deleted = true;
      dictionary->size-=1;
      *err = false;
      return value;
    }
  }

  for (size_t i = 0; i < index; i++) {
    if (dictionary->items[i].key != NULL && strcmp(dictionary->items[i].key, key) == 0 && !dictionary->items[i].deleted) {
      void *value = dictionary->items[i].value;
      // free(dictionary->items[i].key);
      dictionary->items[i].key = NULL;
      dictionary->items[i].value = NULL;
      dictionary->items[i].deleted = true;
      dictionary->size-=1;
      *err = false;
      return value;
    }
  }

  *err = true;
  return NULL;
}


bool dictionary_contains(dictionary_t *dictionary, const char *key) {
  size_t index = hash_function(key, dictionary->capacity);
  if (dictionary->items[index].key == NULL) {
    return false;
  }
  bool err=false;
  dictionary_get(dictionary, key, &err);
  if (err == true) {
    return false;
  }
  return true;
};

size_t dictionary_size(dictionary_t *dictionary) { 
  return dictionary->size; 
};

void dictionary_destroy(dictionary_t *dictionary){
  if(dictionary->destroy!=NULL){
    for (size_t i = 0; i < dictionary->capacity; i++) {
      if (dictionary->items[i].key != NULL) {
        free(dictionary->items[i].key);
      }
    }
  }
  free(dictionary->items);
  free(dictionary);
};

int main(){

    dictionary_t *dic = dictionary_create(NULL);
    char *key = malloc(sizeof("key"));
    int a=5;
    dictionary_put(dic, key, a);


    return 0;
}
