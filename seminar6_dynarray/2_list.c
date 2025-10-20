#include <stdio.h>
#include <stdlib.h>
#include "2_list.h"

List init(size_t n)
{
    List list = {NULL, NULL, 0};
    
    for (size_t i = 0; i < n; ++i) {
        push_back(&list, 0);
    }
    
    return list;
}

void print(const List* pl)
{
    if (pl == NULL) return;
    
    Node* current = pl->head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void push_back(List* pl, int value)
{
    if (pl == NULL) return;
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = pl->tail;
    
    if (pl->tail != NULL) {
        pl->tail->next = new_node;
    }
    pl->tail = new_node;
    
    if (pl->head == NULL) {
        pl->head = new_node;
    }
    
    pl->size++;
}

int pop_back(List* pl)
{
    if (pl == NULL || pl->tail == NULL) {
        fprintf(stderr, "Error: cannot pop from empty list\n");
        exit(1);
    }
    
    Node* last = pl->tail;
    int value = last->value;
    
    if (last->prev != NULL) {
        last->prev->next = NULL;
        pl->tail = last->prev;
    } else {
        pl->head = NULL;
        pl->tail = NULL;
    }
    
    free(last);
    pl->size--;
    
    return value;
}

void push_front(List* pl, int value)
{
    if (pl == NULL) return;
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = pl->head;
    
    if (pl->head != NULL) {
        pl->head->prev = new_node;
    }
    pl->head = new_node;
    
    if (pl->tail == NULL) {
        pl->tail = new_node;
    }
    
    pl->size++;
}

int pop_front(List* pl)
{
    if (pl == NULL || pl->head == NULL) {
        fprintf(stderr, "Error: cannot pop from empty list\n");
        exit(1);
    }
    
    Node* first = pl->head;
    int value = first->value;
    
    if (first->next != NULL) {
        first->next->prev = NULL;
        pl->head = first->next;
    } else {
        pl->head = NULL;
        pl->tail = NULL;
    }
    
    free(first);
    pl->size--;
    
    return value;
}

Node* erase(List* pl, Node* p)
{
    if (pl == NULL || p == NULL) return NULL;
    
    if (p->prev != NULL) {
        p->prev->next = p->next;
    } else {
        pl->head = p->next;
    }
    
    if (p->next != NULL) {
        p->next->prev = p->prev;
    } else {
        pl->tail = p->prev;
    }
    
    Node* next_node = p->next;
    free(p);
    pl->size--;
    
    return next_node;
}

void splice(List* plist, Node* p, List* pother)
{
    if (plist == NULL || pother == NULL || pother->size == 0) return;
    
    if (plist->size == 0) {
        plist->head = pother->head;
        plist->tail = pother->tail;
        plist->size = pother->size;
    } else {
        if (p == plist->head) {
            pother->tail->next = plist->head;
            plist->head->prev = pother->tail;
            plist->head = pother->head;
        } else if (p == NULL) {
            plist->tail->next = pother->head;
            pother->head->prev = plist->tail;
            plist->tail = pother->tail;
        } else {
            pother->head->prev = p->prev;
            pother->tail->next = p;
            p->prev->next = pother->head;
            p->prev = pother->tail;
        }
        plist->size += pother->size;
    }
    
    pother->head = NULL;
    pother->tail = NULL;
    pother->size = 0;
}

void destroy(List* pl)
{
    if (pl == NULL) return;
    
    Node* current = pl->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    
    pl->head = NULL;
    pl->tail = NULL;
    pl->size = 0;
}

void advance(Node** pp, size_t n)
{
    if (pp == NULL || *pp == NULL) return;
    
    Node* current = *pp;
    for (size_t i = 0; i < n && current != NULL; ++i) {
        current = current->next;
    }
    
    *pp = current;
}