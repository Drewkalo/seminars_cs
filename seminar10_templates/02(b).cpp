#include <iostream>
#include <string>

std::string operator*(int n, const std::string& s) {
    std::string result = "";
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            result += s;
        }
    }
    return result;
}

template <typename T>
T triple(const T& x) {
    return (3*x);
}

int main() {
    int a = 10;
    std::cout << "Число: " << triple(a) << std::endl; // Напечатает 30
    std::string b = "Cat";
    std::cout << "Строка: " << triple(b) << std::endl; // Напечатает CatCatCat
}