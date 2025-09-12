#include <stdio.h>
int main()
{
    int n;
    int m;
    scanf("%i %i", &n, &m);
    int result[1000] = {0};
    int total = n * m - 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int temp = 0;
            scanf("%i", &temp);
            result[j] += temp;
        }
    }
    for (int j = 0; j < m; j++)
        printf("%d ", result[j]);

}