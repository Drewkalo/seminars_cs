#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* concat(const char* a, const char* b) {
    int len1 = strlen(a);
    int len2 = strlen(b);
    char* tmp = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    if (tmp == NULL)
        return NULL;
    strcpy(tmp, a);
    strcpy(&tmp[len1], b);
    return tmp;
}
int main() {
    char a[] = "aba";
    char b[] = "bcb";
    char* temp = concat(a, b);
    printf("%s\n", temp);
    free(temp);
}