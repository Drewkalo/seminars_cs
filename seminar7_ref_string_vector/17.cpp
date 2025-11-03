#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

std::vector<std::vector<std::size_t>> calculate_word_lengths(const std::string& filename) {
    std::vector<std::vector<std::size_t>> result;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error" << filename << std::endl;
        return result;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::size_t> line_lengths;
        std::size_t word_length = 0;
        bool in_word = false;
        for (char c : line) {
            if (!std::isspace(c)) {
                word_length++;
                in_word = true;
            } else {
                if (in_word) {
                    line_lengths.push_back(word_length);
                    word_length = 0;
                    in_word = false;
                }
            }
        }
        if (in_word) {
            line_lengths.push_back(word_length);
        }
        result.push_back(line_lengths);
    }
    file.close();
    return result;
}

void print_result(const std::vector<std::vector<std::size_t>>& result) {
    std::cout << "{";
    for (std::size_t i = 0; i < result.size(); ++i) {
        std::cout << "{";
        for (std::size_t j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j];
            if (j < result[i].size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "}";
        if (i < result.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
}

int main() {
    std::ofstream test_file("test.txt");
    test_file << "one two three\n";
    test_file << "hello\n";
    test_file << "axolotl bison cat dog eagle\n";
    test_file.close();
    std::vector<std::vector<std::size_t>> result = calculate_word_lengths("test.txt");
    print_result(result); // Должно напечатать {{3, 3, 5}, {5}, {7, 5, 3, 3, 5}}
}