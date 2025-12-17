#include <iostream>
#include <set>

int main() {
    int m;
    std::cin >> m;
    
    std::set<int> unique;
    
    for (int i = 0; i < m; ++i) {
        int num;
        std::cin >> num;
        unique.insert(num);
    }
    
    for (auto it = unique.begin(); it != unique.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}