#include <iostream>
#include <string>

bool isDomainName(const std::string& str) {
    return str.starts_with("www.") && str.ends_with(".com");
}
int main() {
    std::cout << isDomainName("www.google.com") << std::endl; // Напечатает 1
    std::cout << isDomainName("abc") << std::endl; // Напечатает 0
    std::cout << isDomainName("hello.com") << std::endl; // Напечатает 0
}