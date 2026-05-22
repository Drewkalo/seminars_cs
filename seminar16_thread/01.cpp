#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std::chrono_literals;

void task1(int i) {
    std::cout << "Thread #" << i << " started." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(i));
    std::cout << "Thread #" << i << " finished." << std::endl;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::thread> threads;
    for (int i = 1; i <= n; ++i) {
        threads.emplace_back(task1, i);
    }
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}