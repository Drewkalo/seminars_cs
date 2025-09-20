#include <stdio.h>

enum shape
{
    ROCK,
    PAPER,
    SCISSORS
};

enum result
{
    LOSS,
    DRAW,
    WIN
};

void print_shape(enum shape s)
{
    switch (s)
    {
        case ROCK:
            printf("Rock");
            break;
        case SCISSORS:
            printf("Scissors");
            break;
        case PAPER:
            printf("Paper");
            break;
    }
}

void print_result(enum result r)
{
    switch (r)
    {
        case LOSS:
            printf("Loss");
            break;
        case WIN:
            printf("Win");
            break;
        case DRAW:
            printf("Draw");
            break;
    }
}

enum result get_result(enum shape a, enum shape b)
{
    if (a == b)
        return DRAW;
    
    switch (a)
    {
        case ROCK:
            if (b == SCISSORS)
                return WIN;
            else
                return LOSS;
        case PAPER:
            if (b == SCISSORS)
                return LOSS;
            else
                return WIN;
        case SCISSORS:
            if (b == ROCK)
                return LOSS;
            else
                return WIN;
    }
}

enum shape get_strength(enum shape s)
{
    switch (s) 
    {
        case ROCK:
            return SCISSORS;
        case PAPER:
            return ROCK; 
        case SCISSORS:
            return PAPER;
    }
}

int main()
{
    printf("Rock vs Scissors:\n"); print_result(get_result(ROCK, SCISSORS));
    printf("\n");
    printf("Rock vs Paper:\n"); print_result(get_result(ROCK, PAPER));
    printf("\n");
    printf("Paper vs Rock:\n"); print_result(get_result(PAPER, ROCK));
}