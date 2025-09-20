#include <stdio.h>

int main()
{
    char a[100];
    char b[100];
    scanf("%s", a);
    scanf("%s", b);

    int i = 0;
    while ((a[i] != '\0') && (b[i] != '\0'))
    {
        printf("%c%c", a[i], b[i]);
        i++;
    }
    
    if (a[i] != '\0')
        printf("%s", &a[i]);
    else if (b[i] != '\0')
        printf("%s", &b[i]);
}