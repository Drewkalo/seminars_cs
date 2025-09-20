#include <stdio.h>

void binary(int n)
{
    
    if (n < 2)
    {
        printf("%i", n);
        return;
    }
    
    binary(n / 2);
    printf("%i", n % 2);
}

int main()
{
    int a;
    scanf("%i", &a);
    inary(a);
}