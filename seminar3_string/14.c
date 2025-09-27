#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int main(int argc, char *argv[])
{
    char *input_filename = argv[1];
    char *output_filename = argv[2];
    int key = atoi(argv[3]);

    FILE *input_file = fopen(input_filename, "r");
    FILE *output_file = fopen(output_filename, "w");
    
    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), input_file) != NULL)
    {
        encrypt(buffer, key);
        fputs(buffer, output_file);
    }
    fclose(input_file);
    fclose(output_file);
}