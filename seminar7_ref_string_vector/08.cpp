#include <iostream>
#include <string>
#include <cctype>

void countLetters(const std::string& str, int& numLetters, int&numDigits) {
    for (std::size_t i = 0; i < str.size(); i++ ) {
        if (std::isalpha(str[i])) {numLetters += 1;}
        if (std::isdigit(str[i])) {numDigits += 1;}
    } 
}

int main() {
    std::string s = "Hello12345_xDD_25";
    int numLetters = 0;
    int numDigits = 0;
    countLetters(s, numLetters, numDigits);

    std::cout << "Число букв: " << numLetters << std::endl 
    << "Число цифр: " << numDigits << std::endl;

}