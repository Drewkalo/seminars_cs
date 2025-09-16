#include <stdio.h>
int main()
{
    int n;
    int m;
    int sum = 0;
    scanf("%i %i", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if ((i + j)%2)
                sum -= i*j;
            else
                sum += i*j;
        }
    }
    printf("%i", sum);
}