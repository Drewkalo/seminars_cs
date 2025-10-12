#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct book {
    char title[50];
    int pages;
    float price;
};

void print_book(struct book* b) {
    printf("Book info:\n");
    printf("Title: %s\nPages: %d\nPrice: %g\n\n", b->title, b->pages, b->price);
}

typedef struct book Book;

int main() {
    Book** p = (Book**)malloc(1 * sizeof(Book*));
    *p = (Book*)malloc(1 * sizeof(Book));
    strcpy((*p)->title, "Don Quiexote");
    (*p)->price = 750.0;
    (*p)->pages = 1000;
    print_book(*p);
    free(*p);
    free(p);
}