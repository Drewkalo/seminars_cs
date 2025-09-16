#include <stdio.h>

int cache[1000] = {0};

int trib(int n)
{
    switch (n)
    {
        case 0:
            return 0;
        case 1:
            return 0;
        case 2:
            return 1;
    }
    if (cache[n] == 0)
        cache[n] = trib(n - 1) + trib(n - 2) + trib(n - 3);

    return cache[n];

}

int main()
{
    int a;
    cache[2] = 1;
    scanf("%i", &a);
    printf("%i", trib(a));
}