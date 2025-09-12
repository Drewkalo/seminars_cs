#include <stdio.h>
int main()
{
    int n;
    scanf("%i", &n);
    int max = -2147483648;
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        int a;
        scanf("%i", &a);
        if (a > max)
        {
            max = a;
            count = 1;
        }
        else if (max == a)
        {
            count++;
        }
    }
printf("(%i, %i)", max, count);
}