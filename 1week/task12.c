#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    int A[100][100];
    int B[100][100];
    int C[100][100] = {0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%i", &A[i][j]);
        }
    }
    
    for (int k = 0; k < n; k++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%i", &B[k][j]);
        }
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%i ", C[i][j]);
        }
        printf("\n");
    }
}