#include <stdio.h>
#include <math.h>

double pi(int n)
{
    double result = 0;
    for (int i = 1; i <= n; i++)
        result += (pow(-1, i + 1)) / (2 * i - 1);
    return 4 * result;
}

int main()
{
    int n;
    scanf("%i", &n);
    printf("%lf", pi(n));
}