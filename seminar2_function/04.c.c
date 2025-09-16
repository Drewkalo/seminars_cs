#include <stdio.h>

int sum_of_digits(int a)
{
    int sum = 0;
    while (a >= 1)
    {
        //printf("FLAG1");
        int temp = 0;
        temp = a % 10;
        sum += temp;
        a /= 10;
    }
    return sum;
}

int sum_of_digits_rec(int a)
{
    if (!a)
    {
        return 0;
    }
    return (a % 10) + sum_of_digits(a / 10);
}

int main()
{
    int a;
    scanf("%i", &a);
    printf("%i ", sum_of_digits_rec(a));
}