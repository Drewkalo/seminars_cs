#include <stdio.h>

int count_even(int array[], int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (!(array[i] % 2))
            count += 1;
    }
    return count;
}

int main()
{
    int array[1000] = {0};
    int size;
    scanf("%i", &size);

    for (int i = 0; i < size; i++)
        scanf("%i", &array[i]);
        
    printf("%i", count_even(array, size));
}