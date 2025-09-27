#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_integer(const char *str)
{
    if (str == NULL || *str == '\0')
        return 0;
    if (*str == '+' || *str == '-')
        str++;
    while (*str)
    {
        if (!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        printf("Error: Wrong number of arguments!\n");
        printf("Usage: %s <number> <operator> <number>\n", argv[0]);
        return 0;
    }
    if (!is_integer(argv[1]) || !is_integer(argv[3]))
    {
        printf("Error: Invalid number format!\n");
        return 0;
    }
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[3]);

    if (strlen(argv[2]) != 1)
    {
        printf("Error: Invalid operator, not a single char!\n");
        return 0;
    }
    
    char operator = argv[2][0];
    int result = 0;
    switch (operator)
    {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0)
            {
                printf("Error: Division by zero!\n");
                return 0;
            }
            result = num1 / num2;
            break;
        case '%':
            if (num2 == 0)
            {
                printf("Error: Modul by zero!\n");
                return 0;
            }
            result = num1 % num2;
            break;
        default:
            printf("Error: Invalid operator! Use +, -, *, /, or %%\n");
            return 1;
    }
    
    printf("%i\n", result);
}