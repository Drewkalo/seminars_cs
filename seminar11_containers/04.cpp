#include <iostream>
#include <map>

int main() {
    int n;
    std::cin >> n;
    
    std::map<int, int> freq_map;
    
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        freq_map[num]++;
    }
    
    auto it = freq_map.begin();
    if (it != freq_map.end()) {
        std::cout << it->first;
        ++it;
        for (; it != freq_map.end(); ++it) {
            std::cout << " " << it->first;
        }
    }
    std::cout << "\n";
    
    it = freq_map.begin();
    if (it != freq_map.end()) {
        std::cout << it->second;
        ++it;
        for (; it != freq_map.end(); ++it) {
            std::cout << " " << it->second;
        }
    }
}