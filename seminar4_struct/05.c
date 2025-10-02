#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node* ptr;
};

typedef struct node Node;

int main() {
    Node node1, node2, node3;
    node1.value = 100;
    node2.value = 200;
    node3.value = 300;
    
    node1.ptr = &node2;
    node2.ptr = &node3;
    node3.ptr = &node1;
    
    Node* current = &node1;
    while (1) {
        printf("%d ", current->value);
        current = current->ptr;
    }
}