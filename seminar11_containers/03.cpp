#include <iostream>
#include <set>

int main() {
    int n;
    std::cin >> n;
    std::multiset<int> nums;
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        nums.insert(num);
    }
    for (int num : nums) {std::cout << num << " ";}
}