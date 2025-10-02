#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GAMES 100
#define MAX_TITLE_LENGTH 50

struct game {
    char title[MAX_TITLE_LENGTH];
    double average_rating;
    int ratings_count;
};

typedef struct game Game;

void swap_games(Game* a, Game* b) {
    Game temp = *a;
    *a = *b;
    *b = temp;
}

void sort_games(Game games[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (games[j].average_rating < games[j + 1].average_rating) {
                swap_games(&games[j], &games[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    getchar(); 
    
    Game games[MAX_GAMES];
    int game_count = 0;
    
    for (int i = 0; i < n; i++) {
        char title[MAX_TITLE_LENGTH];
        char temp;
        scanf("%[^:]", title);
        scanf("%c", &temp);
        int k;
        scanf("%d", &k);
        double sum = 0;
        for (int j = 0; j < k; j++) {
            int rating;
            scanf("%d", &rating);
            sum += rating;
        }
        strcpy(games[game_count].title, title);
        games[game_count].average_rating = sum / k;
        games[game_count].ratings_count = k;
        game_count++;
        if (i < n - 1) {
            scanf("%c", &temp);
        }
    }
    sort_games(games, game_count);
    for (int i = 0; i < game_count; i++) {
        printf("%s, %.3f\n", games[i].title, games[i].average_rating);
    }
}