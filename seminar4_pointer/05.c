#include <stdio.h>
#import <math.h>
#define EPS 1e-10
int solve_quadratic(double a, double b, double c, double* px1, double* px2) {
    double discr = b * b - 4 * a * c;
    if (discr < -EPS) {
        return 0;
    }

    else if (fabs(discr) <= EPS) {
        *px1 = -b / (2 * a);
        return 1;
    }
    else {
        double sqrt_d = sqrt(discr);
        *px1 = (-b + sqrt_d) / (2 * a);
        *px2 = (-b - sqrt_d) / (2 * a);
        return 2;
    }
}

int main() {
    double x1, x2;
    int result;
    result = solve_quadratic(1, -3, 2, &x1, &x2);
    printf("x² - 3x + 2 = 0: %d корней\n", result);
    if (result >= 1) printf("x1 = %.2f\n", x1);
    if (result == 2) printf("x2 = %.2f\n", x2);
}