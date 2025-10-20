#include <stdio.h>
#include "2_list.h"

int main() {
    printf("=== Testing Linked List ===\n");
    
    List a = init(0);

    for (int i = 0; i < 5; ++i)
        push_back(&a, 10 * (i + 1));
    for (int i = 0; i < 5; ++i)
        push_front(&a, 100 * (i + 1));
    
    printf("List a: ");
    print(&a);

    printf("%d\n", pop_front(&a));
    printf("%d\n", pop_back(&a));
    
    printf("After pops: ");
    print(&a);

    Node* p = a.head;
    advance(&p, 3);
    p = erase(&a, p);
    printf("After erase: ");
    print(&a);

    List b = init(0);
    for (int i = 0; i < 3; ++i)
        push_back(&b, 1000 * (i + 1));
    
    splice(&a, p, &b);
    printf("After splice - a: ");
    print(&a);
    
    printf("After splice - b: ");
    print(&b);

    destroy(&a);
    destroy(&b);
    
    return 0;
}