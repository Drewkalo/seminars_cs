#include <stdio.h>
#include <math.h>

#define MIN 1e-5

int main()
{
    double x1, y1, r1, x2, y2, r2;
    
    scanf("%lf %lf %lf", &x1, &y1, &r1);
    scanf("%lf %lf %lf", &x2, &y2, &r2);
    
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dist = sqrt(dx*dx + dy*dy);
    
    double sum = r1 + r2;
    double diff = fabs(r1 - r2);
    
    if (fabs(dist - sum) < MIN || fabs(dist - diff) < MIN)
        printf("Touch\n");
    else if (dist < sum && dist > diff)
        printf("Intersect\n");
    else
        printf("Do not intersect\n");
}