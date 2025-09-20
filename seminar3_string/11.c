#include <stdio.h>
#include <string.h>

void safe_strcpy(char* new, size_t new_size, const char* old)
{
    if (new_size == 0)
        return;
    size_t i;
    for (i = 0; (i < new_size - 1) && (old[i] != '\0'); i++)
        new[i] = old[i];
    new[i] = '\0';
}

int main()
{
    char a[8] = "mouse";
    char b[50] = "LARGEmouse";
    
    printf("Before:'%s'\n", a);
    safe_strcpy(a, sizeof(a), b);
    printf("After:'%s'\n", a);
    printf("Length: %zu\n", strlen(a));
}