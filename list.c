#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * newlist = (List *)malloc(sizeof(List));
    newlist->head = NULL;
    newlist->tail = NULL;
    newlist->current = NULL;
     return newlist;
}

void * firstList(List * list) {
    if(list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list->current == NULL) return NULL;
    if(list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    list->current = list->head;
    if (list->current == NULL) return NULL;
    while(list->current->next != NULL){
        list->current = list->current->next;
    }
    return list->current->data;
}

void * prevList(List * list) {
    if (list->current == NULL) return NULL;
    if(list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* newnode = createNode(data);
    if (list->head == NULL){
        list->head = newnode;
        list->tail = newnode;
    }
    else {
    newnode->next = list->current;
    list->head = newnode;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* newnode = createNode(data);
    if (list->head == NULL){
        list->head = newnode;
        list->tail = newnode;
    }
    else {
    if(list->current->next != NULL){
        list->current->next = newnode;
        newnode->next = list->current->next->next;
        newnode->prev = list->current;
        list->current->next->prev = newnode;
    }
    else{
        list->current->next = newnode;
        newnode->next = NULL;
        newnode->prev = list->current;
        list->tail = newnode;
    }
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    void* eliminado = list->current->data;
    if (list->current == list->head){
        list->head = list->current->next;
        list->head->prev = NULL;
        list->current = list->current->next;
        free(list->current); 
    }
    else if (list->current == list->tail){
        list->tail = list->current->prev;
        list->tail->next = NULL;
        list->current = list->current->next;
        free(list->current);
        
    }
    else{
        list->current->prev->next = list->current->next;
        list->current->next->prev = list->current->prev;
        list->current = list->current->next;
        free(list->current);
    }
    return eliminado;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}