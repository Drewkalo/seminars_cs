#pragma once
#include <iostream>
#include <iomanip>
#include <string>

class Number 
{
private:
    static const int base = 100;
    char* data;
    std::size_t size;
    std::size_t capacity;
    void resize(std::size_t new_capacity) {
        char* new_data = new char[new_capacity];
        std::size_t min_size = (size < new_capacity) ? size : new_capacity;
        
        for (std::size_t i = 0; i < min_size; ++i) {
            new_data[i] = data[i];
        }
        for (std::size_t i = min_size; i < new_capacity; ++i) {
            new_data[i] = 0;
        }
        
        delete[] data;
        data = new_data;
        capacity = new_capacity;
        if (size > capacity) {
            size = capacity;
        }
    }

public:
    Number() {
        capacity = 1;
        data = new char[capacity];
        data[0] = 0;
        size = 1;
    }

    Number(int a) {
        if (a == 0) {
            capacity = 1;
            data = new char[capacity];
            data[0] = 0;
            size = 1;
            return;
        }
        int temp = a;
        capacity = 0;
        while (temp != 0) {
            temp /= base;
            capacity++;
        }
        data = new char[capacity];
        size = capacity;
        temp = a;
        for (std::size_t i = 0; i < size; ++i) {
            data[i] = temp % base;
            temp /= base;
        }
    }

    Number(const Number& num) {
        capacity = num.capacity;
        size = num.size;
        data = new char[capacity];
        for (std::size_t i = 0; i < size; ++i) {
            data[i] = num.data[i];
        }
    }

    Number(const std::string& str) {
        if (str.empty()) {
            capacity = 1;
            data = new char[capacity];
            data[0] = 0;
            size = 1;
            return;
        }

        std::size_t str_size = str.length();
        capacity = (str_size + 1) / 2;
        data = new char[capacity];
        for (std::size_t i = 0; i < capacity; ++i) {
            int start_idx = str_size - 2 * (i + 1);
            if (start_idx < 0) {
                start_idx = 0;
                std::string digit_str = str.substr(start_idx, 1);
                data[i] = std::stoi(digit_str);
            } else {
                std::string digit_str = str.substr(start_idx, 2);
                data[i] = std::stoi(digit_str);
            }
        }
        size = capacity;
        while (size > 1 && data[size-1] == 0) {
            size--;
        }
    }

    ~Number() {
        delete[] data;
    }

    Number& operator=(const Number& num) {
        if (this == &num) {
            return *this;
        }
        delete[] data;
        capacity = num.capacity;
        size = num.size;
        data = new char[capacity];
        for (std::size_t i = 0; i < size; ++i) {
            data[i] = num.data[i];
        }
        return *this;
    }

    Number operator+(const Number& num) const {
        Number result;
        std::size_t max_size = (size > num.size) ? size : num.size;
        result.resize(max_size + 1);
        int carry = 0;
        for (std::size_t i = 0; i < max_size + 1; ++i) {
            int sum = carry;
            if (i < size) sum += data[i];
            if (i < num.size) sum += num.data[i];
            result.data[i] = sum % base;
            carry = sum / base;
        }
        result.size = max_size + 1;
        while (result.size > 1 && result.data[result.size-1] == 0) {
            result.size--;
        }
        return result;
    }

    Number& operator+=(const Number& num) {
        *this = *this + num;
        return *this;
    }

    bool isEven() const {
        return (data[0] % 2) == 0;
    }

    Number operator*(const Number& other) const {
        Number result;
        result.resize(size + other.size + 1);
        for (std::size_t i = 0; i < size; ++i) {
            int carry = 0;
            for (std::size_t j = 0; j < other.size; ++j) {
                int product = data[i] * other.data[j] + result.data[i+j] + carry;
                result.data[i+j] = product % base;
                carry = product / base;
            }
            if (carry > 0) {
                result.data[i + other.size] += carry;
            }
        }
        result.size = size + other.size + 1;
        while (result.size > 1 && result.data[result.size-1] == 0) {
            result.size--;
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& out, const Number& num);
};

std::ostream& operator<<(std::ostream& out, const Number& num) {
    out << static_cast<int>(num.data[num.size - 1]);
    for (std::size_t i = 1; i < num.size; ++i) {
        out << std::setfill('0') << std::setw(2) 
               << static_cast<int>(num.data[num.size - 1 - i]);
    }
    return out;
}

Number fibonacci(int n) {
    if (n == 0) return Number(0);
    if (n == 1) return Number(1);
    Number a(0);
    Number b(1);
    Number c(0);
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

Number factorial(int n) {
    Number result(1);
    for (int i = 2; i <= n; ++i) {
        result = result * Number(i);
    }
    return result;
}

int main() {
    Number a("12345678");
    Number b("87654321");
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a is even: " << a.isEven() << std::endl;
    std::cout << "b is even: " << b.isEven() << std::endl;
    std::cout << "F(1000) = " << fibonacci(1000) << std::endl;
    std::cout << "1000! = " << factorial(1000) << std::endl;
}
