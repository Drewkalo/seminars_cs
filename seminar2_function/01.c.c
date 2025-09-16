#include <stdio.h>

int cube(int n)
{
    return n * n * n;
}

int main()
{
    int a;
    scanf("%i", &a);
    printf("%i", cube(a));
}