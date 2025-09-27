#include <stdio.h>

int main()
{
    char a[100000000];
    scanf("%s", a);
    long long result = 0;
    int i = 0;
    while (a[i])
    {
        result += a[i] - '0';
        i++;
    }
    printf("%lld\n", result);
}