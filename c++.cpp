#include <iostream>

int main() {
    #ifdef __cplusplus
        std::cout << "Версия C++: " << __cplusplus << std::endl;
    #endif
    
    // C++20 должен быть 202002L или выше
    #if __cplusplus >= 202002L
        std::cout << "C++20 поддерживается!" << std::endl;
    #else
        std::cout << "C++20 НЕ поддерживается!" << std::endl;
        std::cout << "Текущая версия: " << __cplusplus << std::endl;
    #endif
    
    return 0;
}