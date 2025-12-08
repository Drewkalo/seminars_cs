#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <utility>

template<typename T1, typename T2>
bool hasMoreElements(const T1& container1, const T2& container2) {
    return container1.size() > container2.size();
}

int main() {
    std::vector<int> a {10, 20, 30, 40, 50}; // size() == 5
    std::string b = "Cat";                  // size() == 3
    std::string c = "Elephant";             // size() == 8
    std::array<int, 3> d {10, 20, 30};      // size() == 3

    std::cout << hasMoreElements(a, b) << std::endl; 
    std::cout << hasMoreElements(a, c) << std::endl; 
    std::cout << hasMoreElements(a, d) << std::endl; 
}