#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

void print(const std::vector<int>& v) {
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

void print(const int* a, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;
}

char& get(std::string& str, std::size_t index) {
    if (index >= str.size()) {
        std::cerr << "Error: Index " << index << " out of range for string of size " << str.size() << std::endl;
        std::exit(1);
    }
    return str[index];
}

int& get(std::vector<int>& vec, std::size_t index) {
    if (index >= vec.size()) {
        std::cerr << "Error: Index " << index << " out of range for vector of size " << vec.size() << std::endl;
        std::exit(1);
    }
    return vec[index];
}

int& get(int arr[], std::size_t size, std::size_t index) {
    if (index >= size) {
        std::cerr << "Error: Index " << index << " out of range for array of size " << size << std::endl;
        std::exit(1);
    }
    return arr[index];
}

int main() {
    std::vector<int> v {10, 20, 30, 40, 50};
    get(v, 2) += 1;
    print(v); // Напечатает 10 20 31 40 50
    
    std::string s = "Cat";
    get(s, 0) = 'B';
    std::cout << s << std::endl; // Напечатает Bat
    
    int a[5] = {10, 20, 30, 40, 50};
    get(a, 5, 2) += 1;
    print(a, 5); // Напечатает 10 20 31 40 50
    
    get(v, 10) = 0; // Должен напечатать сообщение об ошибке и выйти из программы
}