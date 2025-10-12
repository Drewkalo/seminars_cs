#include <stdlib.h>
#include <stdio.h>

int main() {
    size_t* p = (size_t*)malloc(1 * sizeof(size_t));
    *p = 123;
    printf("%zu", *p);
    free(p);
}