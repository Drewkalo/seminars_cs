#include <stdio.h>
#define MAX 100

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

/*
void print_matrix(float matrix[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.1f ", matrix[i][j]);
        }
        printf("\n");
    }
}
*/
int main()
{
    float A[MAX][MAX] = {0};
    float B[MAX][MAX] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };
    int n = 3;
    /*
    printf("B:\n");
    print_matrix(B, n);
    */
    assign(A, B, n);
     /*
    printf("\nA:\n");
    print_matrix(A, n);
    */
}