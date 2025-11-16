#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

class Integer 
{
private:
    static const int base = 100;
    std::vector<char> data;
    void removeZeros() {
        while (data.size() > 1 && data.back() == 0) {
            data.pop_back();
        }
    }

public:
    Integer() {
        data.push_back(0);
    }

    Integer(int a) {
        if (a == 0) {
            data.push_back(0);
            return;
        }

        while (a > 0) {
            data.push_back(a % base);
            a /= base;
        }
    }

    Integer(const std::string& str) {
        if (str.empty()) {
            data.push_back(0);
            return;
        }
        std::string temp = str;
        while (!temp.empty()) {
            int length = (temp.length() >= 2) ? 2 : 1;
            std::string digit_str = temp.substr(temp.length() - length, length);
            temp = temp.substr(0, temp.length() - length);
            data.push_back(std::stoi(digit_str));
        }
        removeZeros();
    }

    Integer& operator=(const Integer& num) {
        if (this != &num) {
            data = num.data;
        }
        return *this;
    }

    Integer operator+(const Integer& num) const {
        Integer result;
        result.data.resize(std::max(data.size(), num.data.size()) + 1, 0);
        int carry = 0;
        for (size_t i = 0; i < result.data.size(); ++i) {
            int sum = carry;
            if (i < data.size()) sum += data[i];
            if (i < num.data.size()) sum += num.data[i];
            result.data[i] = sum % base;
            carry = sum / base;
        }
        result.removeZeros();
        return result;
    }

    Integer& operator+=(const Integer& num) {
        *this = *this + num;
        return *this;
    }

    Integer operator*(const Integer& num) const {
        Integer result;
        result.data.resize(data.size() + num.data.size() + 1, 0);
        for (size_t i = 0; i < data.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < num.data.size(); ++j) {
                int product = data[i] * num.data[j] + result.data[i + j] + carry;
                result.data[i + j] = product % base;
                carry = product / base;
            }
            if (carry > 0) {
                result.data[i + num.data.size()] += carry;
            }
        }
        result.removeZeros();
        return result;
    }

    bool isEven() const {
        return (data[0] % 2) == 0;
    }

    friend std::ostream& operator<<(std::ostream& out, const Integer& num);
};

std::ostream& operator<<(std::ostream& out, const Integer& num) {
    if (num.data.empty()) {
        out << "0";
        return out;
    }
    out << static_cast<int>(num.data.back());
    for (int i = num.data.size() - 2; i >= 0; --i) {
        out << std::setfill('0') << std::setw(2) << static_cast<int>(num.data[i]);
    }
    return out;
}

Integer fibonacciInteger(int n) {
    if (n == 0) return Integer(0);
    if (n == 1) return Integer(1);
    
    Integer a(0), b(1), c(0);
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

Integer factorialInteger(int n) {
    Integer result(1);
    for (int i = 2; i <= n; ++i) {
        result = result * Integer(i);
    }
    return result;
}

int main() {
    // Тестирование основных операций
    Integer a("12345678");
    Integer b("87654321");
    
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    
    // Тестирование четности
    std::cout << "a is even: " << a.isEven() << std::endl;
    std::cout << "b is even: " << b.isEven() << std::endl;
    
    // Вычисление F1000
    std::cout << "F(1000) = " << fibonacciInteger(1000) << std::endl;
    
    // Вычисление 1000!
    std::cout << "1000! = " << factorialInteger(1000) << std::endl;
}