#include <stdio.h>

void bob(int n);
void alice(int n);

void alice(int n)
{
    int result = n * 3 + 1;
    printf("Alice: %i\n", result);
    bob(result);
}

void bob(int n)
{
    n /= 2;
    printf("Bob: %d\n", n);
    
    if (n == 1)
        return;
    
    if (n % 2 == 0)
        bob(n);
    else
        alice(n);
}

int main()
{
    int a;
    scanf("%d", &a);
    alice(a);
}