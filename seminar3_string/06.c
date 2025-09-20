#include <stdio.h>
#include <string.h>

int main()
{
    char a[1000];
    scanf("%s", a);
    
    int length = strlen(a);
    
    for (int i = 0; i < length / 2; i++)
    {
        if (a[i] != a[length - 1 - i])
        {
            printf("No\n");
            return 0;
        }
    }
    
    printf("Yes\n");
}