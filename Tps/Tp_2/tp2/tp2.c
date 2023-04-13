#include "tp2.h"
#include <stdlib.h>
#include <stdbool.h>

struct node;
typedef struct node node_t;

struct node {
    void* value;
    node_t* next;
    node_t* prev;
};

struct list {
    node_t* head;
    node_t* tail;
    size_t size;
};

struct list_iter {
    list_t* list;
    node_t* curr;
};

list_t *list_new(){
    list_t* list=(list_t*)malloc(sizeof(list_t));
    if (!list) return NULL;

    list->head=NULL;
    list->tail=NULL;
    list->size=0;
    
    return list;
}

size_t list_length(const list_t *list){
    return list->size;
}

bool list_is_empty(const list_t *list){
    return list_length(list)==0;
}

bool list_insert_head(list_t *list, void *value){
    node_t* newNode=(node_t*)malloc(sizeof(node_t));
    
    if(!newNode) return false;

    newNode->next=list->head;
    newNode->prev=NULL;
    newNode->value=value;
    
    (list_is_empty(list)) ? (list->tail=newNode) : (list->head->prev=newNode);
    
    list->head=newNode;
    list->size+=1;    
    
    return true;
}

bool list_insert_tail(list_t *list, void *value){
    node_t* newNode=(node_t*)malloc(sizeof(node_t));
    
    if(!newNode) return false;

    newNode->prev=list->tail;
    newNode->next=NULL;
    newNode->value=value;
    
    (list_is_empty(list)) ? (list->head=newNode) : (list->tail->next=newNode);
    
    list->tail=newNode;
    list->size+=1;    
    
    return true;
}

void *list_peek_head(const list_t *list){
    if(list_is_empty(list)) return NULL;
    return list->head->value;
}

void *list_peek_tail(const list_t *list){
    if(list->size==0) return NULL;
    return list->tail->value;
}

void *list_pop_head(list_t *list){
    if (list->size==0) return NULL;
    
    void *auxv;
    node_t *aux;

    switch (list_length(list)) {
        case 1:
            auxv = list->head->value;
            aux = list->head;
            list->head = NULL;
            list->tail = NULL;
            free(aux);
            list->size -= 1;
            break;
        case 2:
            auxv = list->head->value;
            aux = list->head;
            list->head = list->tail;
            list->head->prev = NULL;
            free(aux);
            list->size -= 1;
            break;

        default:
            auxv = list->head->value;
            aux = list->head;
            list->head = aux->next;
            list->head->prev = NULL;
            free(aux);
            list->size -= 1;
            break;
    }
    return auxv;
}

void *list_pop_tail(list_t *list){
    if (list->size==0) return NULL;
    
    void *auxv;
    node_t *aux;
    
    switch (list_length(list)) {
        case 1:
            auxv = list->tail->value;
            aux = list->tail;
            list->head = NULL;
            list->tail = NULL;
            free(aux);
            list->size -= 1;
            break;
        case 2:
            auxv = list->tail->value;
            aux = list->tail;
            list->tail = list->head;
            list->tail->next = NULL;
            free(aux);
            list->size -= 1;
            break;
        default:
            auxv = list->tail->value;
            aux = list->tail;
            list->tail = aux->prev;
            list->tail->next = NULL;
            free(aux);
            list->size -= 1;
            break;
    }
    return auxv;
}

void list_destroy(list_t *list, void destroy_value(void *)){  //verificar
    if(destroy_value){
        while(!list_is_empty(list)){
            destroy_value(list_pop_tail(list));
        }
        free(list);
    } else {
        while(!list_is_empty(list)){
            list_pop_tail(list);
        }
        free(list);
    }
}

list_iter_t *list_iter_create_head(list_t *list){
    list_iter_t* iter=(list_iter_t*)malloc(sizeof(list_iter_t));
    if(!iter) return NULL;

    if(list_is_empty(list)){
        iter->list=list;
        iter->curr=NULL;
    } else{
        iter->list=list;
        iter->curr=iter->list->head;
    }
    return iter;
}

list_iter_t *list_iter_create_tail(list_t *list){
    list_iter_t* iter=(list_iter_t*)malloc(sizeof(list_iter_t));
    if(!iter) return NULL;

    if(list_is_empty(list)){
        iter->list=list;
        iter->curr=NULL;
    } else{
        iter->list=list;
        iter->curr=iter->list->tail;
    }
    return iter;
}

bool list_iter_forward(list_iter_t *iter){
    if(iter->list->size==0 || iter->list->size==1 || iter->curr->next==NULL){
        return false;
    } else{
        iter->curr=iter->curr->next;
        return true;
    }
}

bool list_iter_backward(list_iter_t *iter){
    if(iter->list->size==0 || iter->list->size==1 || iter->curr->prev==NULL){
        return false;
    } else{
        iter->curr=iter->curr->prev;
        return true;
    }
}

void *list_iter_peek_current(const list_iter_t *iter){
    if(list_is_empty(iter->list)){
        return NULL;
    } else{
        return iter->curr->value;
    }
}

bool list_iter_at_last(const list_iter_t *iter){
    return !(iter->list->size==0 || iter->curr!=iter->list->tail);
}

bool list_iter_at_first(const list_iter_t *iter){
    return !(iter->list->size==0 || iter->curr!=iter->list->head);
}

void list_iter_destroy(list_iter_t *iter){
    free(iter);
}

bool list_iter_insert_after(list_iter_t *iter, void *value){

    if(list_is_empty(iter->list)){
        if(list_insert_head(iter->list,value)){
            iter->curr=iter->list->head;
            return true;
        } else{
            return false;
        }
    }

    if (list_iter_at_last(iter)) return list_insert_tail(iter->list,value);

    node_t* newNode=(node_t*)malloc(sizeof(node_t));

    if(!newNode){
        return false;
    } else if(list_length(iter->list)==1){
        newNode->prev=iter->list->head;
        iter->list->head->next=newNode;
        iter->list->tail=newNode;
        iter->list->size+=1;
        return true;
    } else{
        newNode->next=iter->curr->next;
        newNode->prev=iter->curr;
        newNode->value=value;

        iter->curr->next=newNode;
        
        iter->list->size+=1;    
        
        return true;
    }
}

bool list_iter_insert_before(list_iter_t *iter, void *value){
    if(list_is_empty(iter->list)){
        if(list_insert_tail(iter->list,value)){
            iter->curr=iter->list->tail;
            return true;
        } else{
            return false;
        }
    }

    if (list_iter_at_first(iter)) return list_insert_head(iter->list,value);
    
    node_t* newNode=(node_t*)malloc(sizeof(node_t));

    if(!newNode){
        return false;
    } else{
        newNode->prev=iter->curr->prev;
        newNode->next=iter->curr;
        newNode->value=value;
            
        iter->curr->prev->next=newNode;
        iter->list->size+=1;    
        
        return true;
    }
}

void *list_iter_delete(list_iter_t *iter){
    if (list_is_empty(iter->list)) return NULL;
    
    node_t *aux;
    void *auxv;
    
    if (list_length(iter->list)==1){
        aux=iter->curr;
        auxv=aux->value;
        iter->list->head=NULL;
        iter->list->tail=NULL;
        iter->list->size=0;
        iter->curr=NULL;
        free(aux);
        return auxv; 
    } else if(list_length(iter->list)==2 || list_iter_at_first(iter)){
        list_iter_forward(iter);
        return list_pop_head(iter->list);
    }

    aux=iter->curr;
    auxv=aux->value;

    if(aux==iter->list->head){
        list_iter_forward(iter);  //hay que aclarar
        list_pop_head(iter->list);
    } else if(aux==iter->list->tail){
        list_iter_backward(iter);  //hay que aclarar
        list_pop_tail(iter->list);
    } else{
        iter->curr->prev->next=aux->next;
        iter->curr->next->prev=aux->prev;
        iter->curr=aux->next;
        iter->list->size-=1;
        free(aux);
    }
    return auxv;
}
