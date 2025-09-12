#include <stdio.h>
int main()
{
    int a;
    int mass[1000];
    scanf("%i", &a);
    for (int i = 0; i < a; i++)
    {
        int temp;
        scanf("%i", &temp);
        mass[i] = temp;
    }
    for (int j = 0; j < 2; j++)
    {
        for (int k = 0; k < a; k++)
        {
            printf("%i ", mass[k]);
        }
    }
}