#include <stdio.h>
#define MAX 100

void assign(float A[MAX][MAX], float B[MAX][MAX], int n);
void power(float A[MAX][MAX], float C[MAX][MAX], int n, int k);
void multiply(float A[MAX][MAX], float B[MAX][MAX], float C[MAX][MAX], int n);

void assign(float A[MAX][MAX], float B[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = B[i][j];
        }
    }
}


void multiply(float A[MAX][MAX], float B[MAX][MAX], float C[MAX][MAX], int n)
{
    float temp[MAX][MAX] = {0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                temp[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    assign(C, temp, n);
}

void power(float A[MAX][MAX], float C[MAX][MAX], int n, int k)
{
    if (k == 1)
    {
        assign(C, A, n);
        return;
    }
    float B[MAX][MAX] = {0};
    assign(B, A, n);
    assign(C, A, n);
    
    for (int i = 1; i < k; i++)
    {
        multiply(A, B, C, n);
        assign(B, C, n);
    }
}

int main()
{
    float A[MAX][MAX] = {0};
    float C[MAX][MAX] = {0}; 
    int n;
    int k;

    scanf("%i", &n);
    scanf("%i", &k);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%f", &A[i][j]);
        }
    }

    power(A, C, n, k);

    printf("Result:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.0f ", C[i][j]);
        }
        printf("\n");
    }
}