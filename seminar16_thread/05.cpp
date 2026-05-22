template <typename RandIt, typename Comparator>
void parallelSort(int n, RandIt start, RandIt finish, Comparator comp) {
    auto dist = std::distance(start, finish);
    if (n <= 1 || dist < 2) {
        std::sort(start, finish, comp);
        return;
    }

    auto segment_size = dist / n;
    std::vector<std::thread> threads;

    for (int i = 0; i < n; ++i) {
        RandIt segment_start = start + i * segment_size;
        RandIt segment_end = (i == n - 1) ? finish : (segment_start + segment_size);
        
        threads.emplace_back([segment_start, segment_end, comp]() {
            std::sort(segment_start, segment_end, comp);
        });
    }

    for (auto& t : threads) t.join();
    for (int i = 1; i < n; ++i) {
        std::inplace_merge(start, start + i * segment_size, start + (i + 1) * segment_size, comp);
    }
}