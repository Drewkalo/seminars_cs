#include <iostream>
#include <algorithm>

template<typename T>
void swapEndianness(T& value) {
    constexpr std::size_t size = sizeof(T); 
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
    std::reverse(bytes, bytes + size);
}

void print_bytes(std::ostream& os, const auto& value) {
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&value);
    for (int i = sizeof(value) - 1; i >= 0; --i) {
        os << std::hex << (int)bytes[i]; 
    }
}

int main() {
    std::cout << std::hex << std::uppercase;
    int a = 0x1A2B3C4D;
    
    std::cout << "int a: ";
    print_bytes(std::cout, a); // Напечатает 1A2B3C4D (при выводе в Big Endian)
    std::cout << std::endl; 
    
    swapEndianness(a);
    
    std::cout << "swap: ";
    print_bytes(std::cout, a); // Напечатает 4D3C2B1A 
    std::cout << std::endl; 
    
    swapEndianness(a);
    
    std::cout << "swap: ";
    print_bytes(std::cout, a); // Напечатает 1A2B3C4D
    std::cout << std::endl; 
    
    short b = 0x1A2B;
    
    std::cout << "short b: ";
    print_bytes(std::cout, b); // Напечатает 1A2B
    std::cout << std::endl;
    
    swapEndianness(b);
    
    std::cout << "swap: ";
    print_bytes(std::cout, b); // Напечатает 2B1A
    std::cout << std::endl;
}