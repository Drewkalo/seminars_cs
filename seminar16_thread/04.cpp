#include <vector>
#include <thread>
#include <algorithm>
#include <iterator>

template <typename RandIt>
RandIt getMax(int n, RandIt start, RandIt finish) {
    auto dist = std::distance(start, finish);
    if (dist <= 0) return finish;
    
    if (n <= 0 || dist < n) n = 1;
    
    auto segment_size = dist / n;
    std::vector<RandIt> results(n);
    std::vector<std::thread> threads;

    for (int i = 0; i < n; ++i) {
        RandIt segment_start = start + i * segment_size;
        RandIt segment_end = (i == n - 1) ? finish : (segment_start + segment_size);
        
        threads.emplace_back([segment_start, segment_end, &results, i]() {
            results[i] = getMax(segment_start, segment_end);
        });
    }

    for (auto& t : threads) t.join();

    RandIt global_max = results[0];
    for (int i = 1; i < n; ++i) {
        if (*results[i] > *global_max) {
            global_max = results[i];
        }
    }
    return global_max;
}