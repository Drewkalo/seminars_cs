#include <stdio.h>
#include <ctype.h>
int main()
{
    char a;
    scanf("%c", &a);

    //a
    if (((65 <= a) && (a <= 90)) || ((97 <= a) && (a <= 122)))
        printf("Letter\n");
    else if ((48 <= a) && (a <= 57))
        printf("Digit\n");
    else
        printf("Other\n");

    //b
    if (((a >= 'A') && (a <= 'Z')) || ((a >= 'a') && (a <= 'z')))
        printf("Letter\n");
    else if ((a >= '0') && (a <= '9'))
        printf("Digit\n");
    else
        printf("Other\n");

    //c
    if (isalpha(a))
        printf("Letter\n");
    else if (isdigit(a))
        printf("Digit\n");
    else
        printf("Other\n");
}
