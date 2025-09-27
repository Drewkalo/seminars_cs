#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{   
    int count = atoi(argv[2]);
    for (int i = 0; i < count; i++)
        printf("%s ", argv[1]);
    printf("\n");
}