#include <stdio.h>

int exchange(int* pa, int b) {
    int old = *pa;
    *pa = b;
    return old;
}

int main() {
    int a = 10;
    printf("%i\n", exchange(&a, 20)); // Напечатает 10
    printf("%i\n", a); // Напечатает 20
    
    return 0;
}