#include <stdio.h>
#include <ctype.h>
int main()
{
    char a;
    scanf("%c", &a);
    if (((65 <= a) && (a <= 90)) || ((97 <= a) && (a <= 122)))
        printf("Letter\n");
    else if ((48 <= a) && (a <= 57))
        printf("Digit\n");
    else
        printf("Other\n");
}
