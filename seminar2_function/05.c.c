#include <stdio.h>
#include <math.h>

int print_binary(int a, int result[])
{
    int current = 0;
    int cycle = 0;
    while (a > 0)
    {
        int temp = 0;
        temp = a % 2;
        result[current] = temp;
        current++;
        if (temp)
        {
            a -= temp * pow(2, cycle);
        }
        cycle++;
    }
    return current;
}

int main()
{
    int result[1000] ={0};
    int a;
    scanf("%i", &a);
    for (int i = 0; i < print_binary(a, result); i++)
    {
        printf("%i", result[i]);
    }
}