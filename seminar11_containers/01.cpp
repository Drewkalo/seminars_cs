#include <iostream>
#include <list>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::list<int> people;
    for (int i = 1; i <= n; ++i) {
        people.push_back(i);
    }
    
    std::vector<int> mask;
    auto current = people.begin();
    
    while (!people.empty()) {
        for (int i = 1; i < m; ++i) {
            ++current;
            if (current == people.end()) {
                current = people.begin();
            }
        }
        mask.push_back(*current);
        current = people.erase(current);
        if (current == people.end() && !people.empty()) {
            current = people.begin();
        }
    }
    
    for (size_t i = 0; i < mask.size() - 1; ++i) {
        std::cout << mask[i] << " ";
    }
    std::cout << mask.back() << "\n" << mask.back() << std::endl;
}