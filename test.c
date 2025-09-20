#include <stdio.h>
void counter(int n)
{
    if (n <= 0)
        return;
    printf("%i ", n);
    counter(n - 1);
}

int main()
{
    int a;
    scanf("%i", &a);
    counter(a);
}