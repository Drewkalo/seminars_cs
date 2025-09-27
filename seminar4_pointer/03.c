#include <stdio.h>
void cube(float* px)
{
    *px = (*px) * (*px) * (*px);
    return;
}
int main()
{
    float a;
    float* p = &a;
    scanf("%f", &a);
    printf("%.3f\n", a);
    cube(p);
    printf("%.3f", a);
}