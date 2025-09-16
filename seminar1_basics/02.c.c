#include <stdio.h>

int main()
{
    int a;
    scanf("%i", &a);
    if (!(a % 2) && (((a <= 20) && (a >= 0)) || ((a > 100) && (a < 200))))
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
}