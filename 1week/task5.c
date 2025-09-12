#include <stdio.h>
int main()
{
    int n;
    int numbers[1000];
    scanf("%i", &n);
    int current = 1;
    int max = n;
    int length = 1;
    numbers[0] = n;
    while (n != 1)
    {
        if (n % 2)
            n = 3 * n + 1;
        else
            n = n / 2;
    numbers[current] = n;
    current++;
    length++;
    if (max < n)
        max = n;
    }
    for (int j = 0; j < current; j++)
    {
        printf("%i ", numbers[j]);
    }
    printf("\nLength = %i, Max = %i\n", length, max);
}