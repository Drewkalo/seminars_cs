#include <stdio.h>

void reverse(int array[], int size)
{
   if (size / 2)
   {
        for (int i = 0; i < (size - 1) / 2; i++)
        {
            int temp = array[i];
            array[i] = array[size - 1 - i];
            array[size - 1 - i] = temp;
        }
   }
   else
   {
        for (int i = 0; i < (size/2) - 1; i++)
        {
            int temp = array[i];
            array[i] = array[size - 1 - i];
            array[size - 1 - i] = temp;
        }
   }
}


int main()
{
    int array[1000] = {0};
    int size;
    scanf("%i", &size);

    for (int i = 0; i < size; i++)
        scanf("%i", &array[i]);

    reverse(array, size);

    for (int i = 0; i < size; i++)
        printf("%i ", array[i]);
}