#include <stdio.h>

int trib(int n, int cache[])
{
    if (cache[n] != 0 || n <= 2)
        return cache[n];

    cache[n] = trib(n - 1, cache) + trib(n - 2, cache) + trib(n - 3, cache);
    return cache[n];
}

int main()
{
    int a;
    int cache[1000] = {0, 0, 1};
    scanf("%i", &a);
    printf("%i", trib(a, cache));
}