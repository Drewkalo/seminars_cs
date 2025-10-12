#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct book {
    char* title;
    int pages;
    float price;
};

typedef struct book Book;

struct library {
    Book* books;
    int number_of_books;
};

typedef struct library Library;


void print_book(struct book* b) {
    printf("Book info:\n");
    printf("Title: %s\nPages: %i\nPrice: %.1f\n\n", b->title, b->pages, b->price);
}


void library_create(Library* lib, int num) {
    lib->number_of_books = num;
    lib->books = (Book*)malloc(num * sizeof(Book));
    for (int i = 0; i < num; i++) {
        lib->books[i].title = NULL;
        lib->books[i].price = (float)0;
        lib->books[i].pages = 0;
    }
}
void library_set(Library* lib, int i, const char* title, int pages, float price) {
    if (lib == NULL || i < 0 || i >= lib->number_of_books) 
        return;
    if (lib->books[i].title != NULL)
        free(lib->books[i].title);
    lib->books[i].title = (char*)malloc((strlen(title) + 1) * sizeof(char));
    strcpy(lib->books[i].title, title);
    (lib->books)[i].pages = pages;
    (lib->books)[i].price = price;
}

Book* library_get(Library* lib, int i) {
    if (lib != NULL && i >= 0 && i < lib->number_of_books)
        return &(lib->books[i]);
    return NULL;
}

void library_print(Library* lib) {
    if (lib == NULL)
        return;
    for (int i = 0; i < lib->number_of_books; i++) 
        print_book(&(lib->books[i]));
}

void library_destroy(Library* lib) {
    if (lib == NULL)
        return;
    for (int i = 0; i < lib->number_of_books; i++) {
        if (lib->books[i].title != NULL) {
            free(lib->books[i].title);
            lib->books[i].title = NULL;
        }
    }
    free(lib->books);
    lib->books = NULL;
    lib->number_of_books = 0;
}

int main() {
    Library a;
    library_create(&a, 3);
    library_set(&a, 0, "Don Quixote", 1000, 750.0);
    library_set(&a, 1, "Oblomov", 400, 250.0);
    library_set(&a, 2, "The Odyssey", 500, 500.0);
    
    printf("All books in library:\n");
    library_print(&a);
    
    printf("\nSecond book:\n");
    Book* second_book = library_get(&a, 1);
    if (second_book != NULL)
        print_book(second_book);
    
    library_destroy(&a);
    printf("After destruction: books = %p, number_of_books = %d\n", (void*)a.books, a.number_of_books);
}
