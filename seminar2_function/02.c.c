#include <stdio.h>

int is_even(int n)
{
    return !(n % 2);
}

int main()
{
    //int a;
    //scanf("%i", &a);
    //printf("%i", is_even(a));
    printf("%i\n", is_even(90));
    printf("%i\n", is_even(91));

}