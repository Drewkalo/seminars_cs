#include <stdio.h>
#import <math.h>
#define EPS 1e-10
int solve_quadratic(double a, double b, double c, double* px1, double* px2)
{
    int discr = b*b - 4 * a * c;
    if (discr < -EPS)
    {
        return 0;
    }
    else if (fabs(discr) <= EPS)
    {
        *px1 = -b / (2 * a);
        return 1;
    }
    else
    {
        *px1 = (-b + pow(discr, 0.5)) / (2 * a);
        *px2 = (-b - pow(discr, 0.5)) / (2 * a);
        return 2;
    }
}

int main()
{
    double a = 0;
    double b = 0;
    double c = 0;
    scanf("%lld %lld %lld", &a, &b, &c);
    double res1;
    double res2;
    double* px1 = &res1;
    double* px2 = &res2;
    int tmp = solve_quadratic(a, b, c, px1, px2);
    if (tmp == 2)
        printf("%lld, %lld", *px1, *px2);
    else if (tmp == 1)
        printf("%lld", *px1);
    else
        printf("There are no solve");
}