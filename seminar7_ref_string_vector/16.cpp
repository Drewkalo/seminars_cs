#include <iostream>
#include <string>
#include <vector>

// Функция split
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::size_t start = 0;
    std::size_t end = str.find(delimiter);
    
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    result.push_back(str.substr(start));
    return result;
}

int main() {
    std::string data = "apple,banana,cherry,durian";
    char delimiter = ',';

    std::vector<std::string> parts = split(data, delimiter);
    for (std::size_t i = 0; i < parts.size(); ++i)
        std::cout << parts.at(i) << std::endl;
}