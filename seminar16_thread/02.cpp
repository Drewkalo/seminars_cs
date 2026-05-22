#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

void create_thread(int i, int max_n) {
    if (i > max_n) return;

    std::cout << "Thread #" << i << " started." << std::endl;
    std::this_thread::sleep_for(200ms);

    if (i < max_n) {
        std::thread next(create_thread, i + 1, max_n);
        next.join();
    }

    std::this_thread::sleep_for(200ms);
    std::cout << "Thread #" << i << " finished." << std::endl;
}

int main() {
    int n;
    std::cin >> n;
    if (n > 0) {
        std::thread t(create_thread, 1, n);
        t.join();
    }
    return 0;
}