#include <stdio.h>
#include <stdlib.h>

float* get_geometric_progression(float a, float r, int n) {
    float* p = (float*)malloc(n * sizeof(float));
    p[0] = a;
    for (int i = 1; i < n; i++) {
        p[i] = (float)(p[i-1] * r);
    }
    return p;
}
int main() {
    float* temp = get_geometric_progression(1.0, 3.0, 10);
    for (int i = 0; i < 10; i++) {
        printf("%.2f ", temp[i]);
    }
    free(temp);
}