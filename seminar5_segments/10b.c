#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000000

int main()
{
    printf("Attempting to allocate 1GB in heap...\n");
    char* data = (char*)malloc(SIZE);
    if (data == NULL) {
        printf("Memory allocation failed! Probably not enough contiguous virtual memory.\n");
        return 1;
    }
    
    printf("Memory allocated successfully (virtual address space reserved).\n");

    getchar();
    printf("1. Setting first char to 'A'\n");
    data[0] = 'A';

    getchar();
    printf("2. Setting last char to 'B'\n");
    data[SIZE - 1] = 'B';

    getchar();
    printf("3. Printing first char = %c\n", data[0]);

    getchar();
    printf("4. Printing last char = %c\n", data[SIZE - 1]);

    getchar();
    printf("5. Setting many chars to X\n");
    for (size_t i = 0; i < SIZE; i += 1000)
        data[i] = 'X';

    getchar();
    printf("6. Printing some set chars\n");
    for (size_t i = 0; i < 1000; i += 100)
        printf("%c ", data[i]);

    getchar();
    
    free(data);
    printf("Memory freed.\n");
    getchar();
}