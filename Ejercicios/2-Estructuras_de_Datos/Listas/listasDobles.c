#include <stdio.h>
#include <malloc.h>

typedef struct Node{
    int value;
    struct Node* next;
    struct Node* prev;
}Node;

typedef struct List{
    Node* head;
    Node* tail;
    size_t size;
}List;


List insert_first(List list, int v){
    Node *newNode;
    
    newNode= (Node*) malloc(sizeof(Node));
    if(newNode==NULL) return list;
    
    newNode->value=v;
    newNode->prev=NULL;
    newNode->next=list.head;

    if (list.head==NULL){
        list.tail=newNode;
    } else{
        list.head->prev=newNode;
    }
    list.head=newNode;
    list.size+=1;
    return list;
}

List insert_last(List list, int v){
    Node *newNode;
    
    newNode= (Node*) malloc(sizeof(Node));
    if(newNode==NULL) return list;
    
    newNode->value=v;
    newNode->prev=list.tail;
    newNode->next=NULL;

    if (list.tail==NULL){
        list.head=newNode;
    } else{
        list.tail->next=newNode;
    }
    list.tail=newNode;
    list.size+=1;
    return list;
}

List prints(List list){
    Node *p, *aux;
    p=list.head;
    while(p!=NULL){
        aux=p;
        p=p->next;
        printf("%d\n",aux->value);
        free(aux);
    }
    list.head=NULL;
    list.tail=NULL;
    list.size=0;
    free(p);
    return list;
}

int main(){

    List l;
    l.head=NULL;
    l.tail=NULL;
    l.size=0;
    l=insert_last(l,3);
    l=insert_first(l,2);
    l=insert_last(l,4);
    l=insert_first(l,1);
    l=prints(l);

    return 0;
}
