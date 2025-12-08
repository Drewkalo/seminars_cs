#include <iostream>
#include <vector>
#include <utility>
#include <string>

template<typename T>
std::pair<T, T> minmax(const std::vector<T>& v) {
    if (v.empty()) {
        exit(1);
    }

    T current_min = v[0];
    T current_max = v[0];

    for (auto current : v) {
        const T& element = current;
     
        if (element < current_min) {current_min = element;}
        if (element > current_max) {current_max = element;}
    }
    return std::pair<T, T>(current_min, current_max);
}

int main() {
    std::vector<int> a {60, 10, 40, 80, 30};
    auto am = minmax(a);
    std::cout << "int: " << am.first << " " << am.second << std::endl; 
    
    std::vector<std::string> b {"Cat", "Dog", "Mouse", "Camel", "Wolf"};
    auto bm = minmax(b);
    std::cout << "string: " << bm.first << " " << bm.second << std::endl; 

    std::vector<std::pair<int, int>> c {{10, 90}, {30, 10}, {20, 40}, {10, 50}};
    auto cm = minmax(c);
    std::cout << "pair<int, int> min: " << cm.first.first << " " << cm.first.second << std::endl;
    std::cout << "pair<int, int> max: " << cm.second.first << " " << cm.second.second << std::endl;
}