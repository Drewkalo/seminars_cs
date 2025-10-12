#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** get_test_strings() {
    char** arr = malloc(4 * sizeof(char*));
    arr[0] = (char*)malloc(4 * sizeof(char));
    strcpy(arr[0], "Cat");
    arr[1] = (char*)malloc(9 * sizeof(char));
    strcpy(arr[1], "Elephant");
    arr[2] = (char*)malloc(6 * sizeof(char));
    strcpy(arr[2], "Mouse");
    arr[3] = NULL;
    return arr;
}

void print_strings(const char** str_array) {
    if (str_array == NULL) 
        return;
    
    for (int i = 0; str_array[i] != NULL; i++)
        printf("%s\n", str_array[i]);
}

size_t* get_sizes(const char** str_array) {
    if (str_array == NULL)
        return NULL;
    
    int count = 0;
    while (str_array[count] != NULL)
        count++;

    size_t* sizes = malloc(count * sizeof(size_t));
    if (sizes == NULL)
        return NULL;
    
    for (int i = 0; i < count; i++)
        sizes[i] = strlen(str_array[i]);

    return sizes;
}

char** load_lines(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }
    
    int line_count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n')
            line_count++;
    }
    
    char** lines = malloc((line_count + 1) * sizeof(char*));
    if (lines == NULL) {
        fclose(file);
        return NULL;
    }
    
    fseek(file, 0, SEEK_SET);
    int* line_lengths = malloc((line_count + 1) * sizeof(int));
    if (line_lengths == NULL) {
        fclose(file);
        free(lines);
        return NULL;
    }
    
    for (int i = 0; i < line_count; i++) {
        line_lengths[i] = 0;
        while ((ch = fgetc(file)) != EOF && ch != '\n') {
            line_lengths[i]++;
        }
        if (ch == EOF) break;
    }
    
    fseek(file, 0, SEEK_SET);
    char* buffer = malloc(1024 * sizeof(char));
    
    for (int i = 0; i < line_count; i++) {
        if (fgets(buffer, 1024, file) == NULL)
            break;
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
        
        lines[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        if (lines[i] != NULL)
            strcpy(lines[i], buffer);
    }
    
    lines[line_count] = NULL;
    free(line_lengths);
    free(buffer);
    fclose(file);
    return lines;
}


void destroy_strings(char*** p_string_array) {
    if (p_string_array == NULL || *p_string_array == NULL)
        return;
    
    char** arr = *p_string_array;
    
    for (int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    *p_string_array = NULL;
}

int compare_strings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void sort_strings(char** words) {
    if (words == NULL) return;
    
    int count = 0;
    while (words[count] != NULL) count++;

    qsort(words, count, sizeof(char*), compare_strings);
}

void line_sorter(const char* input_filename, const char* output_filename) {
    char** lines = load_lines(input_filename);
    if (lines == NULL) {
        printf("Error: Cannot load lines from %s\n", input_filename);
        return;
    }
    
    sort_strings(lines);
    
    FILE* output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("Error: Cannot open output file %s\n", output_filename);
        destroy_strings(&lines);
        return;
    }
    
    for (int i = 0; lines[i] != NULL; i++) {
        fprintf(output_file, "%s\n", lines[i]);
    }
    
    fclose(output_file);
    destroy_strings(&lines);
    printf("File %s sorted and saved to %s\n", input_filename, output_filename);
}


int main(int argc, char* argv[]) {
    printf("1. Test strings:\n");
    char** test_strings;
    test_strings = get_test_strings();
    print_strings((const char**)test_strings);
    

    printf("\n2. String sizes:\n");
    size_t* sizes = get_sizes((const char**)test_strings);
    for (int i = 0; test_strings[i] != NULL; i++) {
        printf("'%s' - %zu characters\n", test_strings[i], sizes[i]);
    }
    free(sizes);
    
    printf("\n3. Sorted strings:\n");
    sort_strings(test_strings);
    print_strings((const char**)test_strings);

    destroy_strings(&test_strings);
    printf("4. After destruction: %p\n", (void*)test_strings);
    if (argc == 3) {
        line_sorter(argv[1], argv[2]);
    } else if (argc > 1) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
    }
    
    return 0;
}