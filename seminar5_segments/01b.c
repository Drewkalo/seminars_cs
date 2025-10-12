#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
    char* p = (char*)malloc(9 * sizeof(char));
    strcpy(p, "Elephant");
    printf("%s", p);
    free(p);
}