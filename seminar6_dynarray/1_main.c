#include <stdio.h>
#include "1_dynarray.h"

void test_new_functions() {
    printf("=== Testing New Dynamic Array Functions ===\n");
    
    Dynarray arr;
    init(&arr, 3);
    
    // Тестирование базовых операций
    printf("Initial: ");
    print(&arr);
    
    push_back(&arr, 10);
    push_back(&arr, 20);
    push_back(&arr, 30);
    printf("After push_back: ");
    print(&arr);
    
    // Тестирование pop_back
    printf("Popped: %d\n", pop_back(&arr));
    printf("After pop_back: ");
    print(&arr);
    
    // Тестирование resize
    resize(&arr, 5);
    printf("After resize to 5: ");
    print(&arr);
    
    resize(&arr, 2);
    printf("After resize to 2: ");
    print(&arr);
    
    // Тестирование shrink_to_fit
    printf("Before shrink - size: %zu, capacity: %zu\n", arr.size, arr.capacity);
    shrink_to_fit(&arr);
    printf("After shrink - size: %zu, capacity: %zu\n", arr.size, arr.capacity);
    
    // Тестирование копий
    push_back(&arr, 40);
    push_back(&arr, 50);
    
    Dynarray shallow = shallow_copy(&arr);
    Dynarray deep = deep_copy(&arr);
    
    printf("Original: ");
    print(&arr);
    printf("Shallow: ");
    print(&shallow);
    printf("Deep: ");
    print(&deep);
    
    // Изменяем оригинал и смотрим на копии
    set(&arr, 0, 999);
    printf("After modifying original:\n");
    printf("Original: ");
    print(&arr);
    printf("Shallow (changed): ");
    print(&shallow);
    printf("Deep (unchanged): ");
    print(&deep);
    
    // Очистка
    destroy(&arr);
    destroy(&deep);
    // Не вызываем destroy для shallow - он разделяет данные с оригиналом
}

int main() {
    test_new_functions();
    return 0;
}