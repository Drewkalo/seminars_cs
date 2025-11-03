#include <iostream>

struct Book {
    std::string title;
    int pages;
    float price;
};
bool isExpensive(const Book& a) {
    if (a.price > 1000) {return true;}
    else {return false;}
}
int main() {
    Book p0 = {"Hello", 500, 999.0};
    Book p1 = {"world", 500, 2000.0};
    std::cout << isExpensive(p0) << std::endl;
    std::cout << isExpensive(p1) << std::endl;
}