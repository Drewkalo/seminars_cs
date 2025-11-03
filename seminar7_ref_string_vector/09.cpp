#include <iostream>

std::string repeat(const int& n) {
    std::string str;
    if (n < 0) {return "";}
    for (std::size_t i = 0; i < n; i++) {str += std::to_string(n);}
    return str;
} 

int main()
{
    std::cout << repeat(5) << std::endl; // Должно напечатать 55555
    std::cout << repeat(10) << std::endl; // Должно напечатать 10101010101010101010
    std::cout << repeat(-1) << std::endl; // Не должно ничего печатать
    }