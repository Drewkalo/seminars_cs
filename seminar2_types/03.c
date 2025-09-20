#include <stdio.h>

float yearfrac(int year, int day)
{
    if ((year % 4) == 0)
        return day / 366.;
    return day / 365.;
}

int main()
{
    int day, year;
    scanf("%i %i", &year, &day);
    printf("%.5f", yearfrac(year, day));
}