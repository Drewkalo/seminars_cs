#include <thread>
#include <vector>
#include <functional>

template <typename Func, typename... Args>
void iterate(int n, Func f, Args&&... args) {
    std::vector<std::thread> threads;
    threads.reserve(n);

    for (int i = 0; i < n; ++i) {
        threads.emplace_back(f, std::forward<Args>(args)...);
    }

    for (auto& t : threads) {
        t.join();
    }
}