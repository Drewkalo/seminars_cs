#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void line_by_number(FILE* input_fp, FILE* output_fp, int line_num)
{
    char cache[512];
    int curr_line = 1;
    
    while (fgets(cache, sizeof(cache), input_fp) != NULL)
    {
        if (curr_line == line_num)
        {
            fputs(cache, output_fp);
            return;
        }
        curr_line++;
    }
}

int colon_pos(char str[])
{
    int id = 0;
    while (str[id] != '\0')
    {
        if (str[id] == ':')
            return id;
        id++;
    }
    return -1;
}

int is_number(char str[])
{
    int curr = 0;
    while (str[curr] != '\0')
    {
        if (!(isdigit(str[curr])))
            return 0;
        curr++;
    }
    return 1;
}

void line_by_range(FILE* input_fp, FILE* output_fp, int start, int end)
{
    char cache[512];
    int curr_line = 1;
    
    while (fgets(cache, sizeof(cache), input_fp) != NULL)
    {
        if (curr_line >= start && curr_line < end)
        {
            fputs(cache, output_fp);
        }
        curr_line++;
        if (curr_line >= end)
            return; 
    }
}

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        printf("Error: Wrong number of arguments! Usage: %s <input_file> <output_file> <lines>\n", argv[0]);
        exit(1);
    }

    FILE* input_fp = fopen(argv[1], "r");
    if (input_fp == NULL)
    {
        printf("Error: File %s does not exist!\n", argv[1]);
        exit(1);
    }

    FILE* output_fp = fopen(argv[2], "w");
    if (output_fp == NULL)
    {
        printf("Error: Cannot create output file %s!\n", argv[2]);
        fclose(input_fp);
        exit(1);
    }

    char* input = argv[3];
    int position = colon_pos(input);
    
    if (position == -1)
    {   
        if (is_number(input))
        {
            int num = atoi(input);
            if (num > 0)
            {
                line_by_number(input_fp, output_fp, num);
            }
            else
            {
                printf("Error: Wrong lines format!\n");
                fclose(input_fp);
                fclose(output_fp);
                exit(1);
            }
        }
        else
        {
            printf("Error: Wrong line format!\n");
            fclose(input_fp);
            fclose(output_fp);
            exit(1);
        }
    }
    else
    {
        char first[32] = {0};
        char second[32] = {0};
        int i;
        
        for (i = 0; i < position && input[i] != '\0'; i++)
            first[i] = input[i];
        first[i] = '\0';
        
        int j = 0;
        for (i = position + 1; input[i] != '\0'; i++, j++)
            second[j] = input[i];
        second[j] = '\0';

        if (first[0] == '\0' || second[0] == '\0')
        {
            printf("Error: Wrong line format!\n");
            fclose(input_fp);
            fclose(output_fp);
            exit(1);
        }

        if (is_number(first) && is_number(second))
        {
            int start = atoi(first);
            int end = atoi(second);

            if (start > 0 && end > 0)
            {
                if (start < end)
                {
                    line_by_range(input_fp, output_fp, start, end);
                }
                else
                {
                    printf("Error: Wrong lines format!\n");
                    fclose(input_fp);
                    fclose(output_fp);
                    exit(1);
                }
            } 
            else
            {
                printf("Error: Wrong lines format!\n");
                fclose(input_fp);
                fclose(output_fp);
                exit(1);
            }
        }
        else
        {
            printf("Error: Wrong line format!\n");
            fclose(input_fp);
            fclose(output_fp);
            exit(1); 
        }
    }
    
    fclose(input_fp);
    fclose(output_fp);
}