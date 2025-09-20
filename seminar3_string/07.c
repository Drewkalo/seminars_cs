#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encrypt(char* str, int k)
{
    k = k % 26;
    if (k < 0) 
        k += 26;
    
    int length = strlen(str);
    for (int i = 0; i < length; i++)
    {
        if (isalpha(str[i]))
        {
            if (isupper(str[i]))
                str[i] = 'A' + (str[i] - 'A' + k) % 26;
            else
                str[i] = 'a' + (str[i] - 'a' + k) % 26;
        }
    }
}

int main()
{
    char a[1000];
    int k;
    scanf("%i ", &k);
    scanf("%[^\n]", a);
    encrypt(a, k);
    printf("%s\n", a);
}