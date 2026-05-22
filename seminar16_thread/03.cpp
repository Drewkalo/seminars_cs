#include <vector>
#include <thread>
#include <algorithm>
#include <limits>
#include <cstdint>

uint64_t getMaxPar(int n, const std::vector<uint64_t>& v) {
    size_t size = v.size();
    size_t chunk = size / n;
    std::vector<uint64_t> results(n);
    std::vector<std::thread> threads;

    for (int i = 0; i < n; ++i) {
        size_t start = i * chunk;
        size_t end = (i == n - 1) ? size : (i + 1) * chunk;
        
        threads.emplace_back([&v, start, end, &results, i]() {
            uint64_t max_val = v[start];
            for (size_t j = start + 1; j < end; ++j) {
                if (v[j] > max_val) max_val = v[j];
            }
            results[i] = max_val;
        });
    }

    for (auto& t : threads) t.join();
    
    uint64_t final_max = results[0];
    for (uint64_t val : results) {
        if (val > final_max) final_max = val;
    }
    return final_max;
}