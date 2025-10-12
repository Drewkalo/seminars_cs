#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char** p = (char**)malloc(sizeof(char*));
    *p = (char*)malloc(14 * sizeof(char));
    strcpy(*p, "Cats and Dogs");
    printf("%s", *p);
    free(*p);
    free(p);
}