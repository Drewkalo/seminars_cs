#include <stdio.h>

int main()
{
    int a;
    scanf("%i", &a);
    for (int j = 1; j <= a; j++ )
    {
        printf("%3i -> %3i -> %3i\n", j, j * j, j * j * j);
    }
}