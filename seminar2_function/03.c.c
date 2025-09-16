#include <stdio.h>

void print_even(int a, int b)
{
    if (a % 2)
    {
        a += 1;
    }
    while (a <= b)
    {
        printf("%i ", a);
        a += 2;
    }
    printf("\n");
}

int main()
{
    int a;
    int b;
    scanf("%i", &a);
    scanf("%i", &b);

    print_even(a, b);
    //printf("%i, %i", a, b);
}