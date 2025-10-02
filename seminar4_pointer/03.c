#include <stdio.h>
void cube(float* px) {
    *px = (*px) * (*px) * (*px);
    return;
}
int main() {
    float a;
    scanf("%f", &a);
    cube(&a);
    printf("%.3f", a);
}