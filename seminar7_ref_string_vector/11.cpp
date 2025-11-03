#include <iostream>
#include <string>
#include <vector>

void print(const std::vector<int>& v) {
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

void doubling(std::vector<int>& v) {
    std::size_t original_size = v.size();
    v.reserve(original_size * 2);
    
    for (std::size_t i = 0; i < original_size; ++i) {
        v.push_back(v[i]);
    }
}

int main() {
    std::vector<int> v {10, 20, 30};
    doubling(v);
    print(v); // Напечатает 10 20 30 10 20 30
}