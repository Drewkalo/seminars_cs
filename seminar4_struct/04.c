#include <stdio.h>
#include <stddef.h>

struct cat {
    char x;
    size_t y;
};

struct dog {
    size_t y;
    char x;
};

struct mouse {
    char x;
    char y;
    size_t z;
};

struct rat {
    char x;
    size_t z;
    char y;
};

struct fox {
    char x;
    struct mouse y;
};

int main() {
    printf("1. char: sizeof = %zu, alignof = %zu\n", sizeof(char), _Alignof(char));
    printf("2. int: sizeof = %zu, alignof = %zu\n", sizeof(int), _Alignof(int));
    printf("3. size_t: sizeof = %zu, alignof = %zu\n", sizeof(size_t), _Alignof(size_t));
    printf("4. int[10]: sizeof = %zu, alignof = %zu\n", sizeof(int[10]), _Alignof(int[10]));
    printf("5. int*: sizeof = %zu, alignof = %zu\n", sizeof(int*), _Alignof(int*));
    printf("6. cat: sizeof = %zu, alignof = %zu\n", sizeof(struct cat), _Alignof(struct cat));
    printf("7. dog: sizeof = %zu, alignof = %zu\n", sizeof(struct dog), _Alignof(struct dog));
    printf("8. mouse: sizeof = %zu, alignof = %zu\n", sizeof(struct mouse), _Alignof(struct mouse));
    printf("9. rat: sizeof = %zu, alignof = %zu\n", sizeof(struct rat), _Alignof(struct rat));
    printf("10. fox: sizeof = %zu, alignof = %zu\n", sizeof(struct fox), _Alignof(struct fox));
}