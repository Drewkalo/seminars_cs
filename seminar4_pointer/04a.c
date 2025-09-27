#include <stdio.h>
void mult2(float* px, size_t n)
{
    for (int i = 0; i < n; i++)
        *(px + i) *= 2;
    return;
}

int main()
{
    float mass[5] = {1, 2, 3, 4, 5};
    float* p = &mass[0];
    mult2(p, 5);
    for (int i = 0; i < 5; i++)
        printf("%.3f ", mass[i]);
}