#include <stdio.h>
int main()
{
    int n;
    scanf("%i", &n);
    int numbers[10000];
    int sums[10000];
    
    for (int i = 0; i < n; i++)
    {
        scanf("%i", &numbers[i]);
        
        int num = numbers[i];
        if (num < 0) 
            num = -num;
        
        int sum = 0;
        while (num > 0)
        {
            sum += num % 10;
            num /= 10;
        }
        sums[i] = sum;
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (sums[j] > sums[j + 1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
                int temp_sum = sums[j];
                sums[j] = sums[j + 1];
                sums[j + 1] = temp_sum;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}