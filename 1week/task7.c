#include <stdio.h>
int main()
{
    int a;
    int b;
    int c;
    int numbers[1000];
    int border = 0;
    scanf("%i %i %i", &a, &b, &c);
    while (a%c)
        a++;
    while (a <= b)
    {
        numbers[border] = a;
        a += c;
        border++;
    }
    for (int i = 0; i < border; i++)
        printf("%i ", numbers[i]);
}