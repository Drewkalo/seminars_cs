#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

int main()
{
    printf("char %zu\n", sizeof(char));
    printf("short %zu\n", sizeof(short));
    printf("int %zu\n", sizeof(int));
    printf("long long %zu\n", sizeof(long long));
    printf("float %zu\n", sizeof(float));
    printf("double %zu\n", sizeof(double));
    printf("int32_t %zu\n", sizeof(int32_t));
    printf("uint32_t %zu\n", sizeof(uint32_t));
    printf("int8_t %zu\n", sizeof(int8_t));
    printf("size_t %zu\n", sizeof(size_t));
    printf("int[100] %zu\n", sizeof(int[100]));
    printf("char[100] %zu\n", sizeof(char[100]));
}