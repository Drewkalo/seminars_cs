#pragma once
#include <cmath>
#include <iostream>

struct Complex 
{
    float re;
    float im;
};

Complex operator+(Complex a, Complex b) 
{
    Complex result = {a.re + b.re, a.im + b.im};
    return result;
}

Complex operator-(Complex a, Complex b) 
{
    Complex result = {a.re - b.re, a.im - b.im};
    return result;
}

Complex operator*(Complex a, Complex b) 
{
    Complex result = {a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re};
    return result;
}

Complex operator/(Complex a, Complex b) 
{
    float bSquared = b.re * b.re + b.im * b.im;
   
    Complex result;
    result.re = (a.re * b.re + a.im * b.im) / bSquared;
    result.im = (a.im * b.re - a.re * b.im) / bSquared;
    return result;
}

Complex operator+(Complex a, float b) 
{
    Complex result = {a.re + b, a.im};
    return result;
}

Complex operator+(float a, Complex b) 
{
    return b + a;
}

Complex operator-(Complex a, float b) 
{
    Complex result = {a.re - b, a.im};
    return result;
}

Complex operator-(float a, Complex b) 
{
    return b - a;
}

Complex operator*(Complex a, float b) 
{
    Complex result = {a.re * b, a.im * b};
    return result;
}

Complex operator*(float a, Complex b) 
{
    return b * a;
}

Complex operator/(Complex a, float b) 
{
    Complex result = {a.re / b, a.im / b};
    return result;
}

Complex operator/(float a, Complex b) 
{
    Complex ac = {a, 0.0f};
    return ac / b;
}

Complex& operator+=(Complex& a, Complex b) 
{
    a.re += b.re;
    a.im += b.im;
    return a;
}

Complex& operator-=(Complex& a, Complex b) 
{
    a.re -= b.re;
    a.im -= b.im;
    return a;
}


Complex& operator+=(Complex& a, float b) 
{
    a.re += b;
    return a;
}

Complex& operator-=(Complex& a, float b) 
{
    a.re -= b;
    return a;
}

Complex& operator*=(Complex& a, float b) 
{
    a.re *= b;
    a.im *= b;
    return a;
}

Complex& operator/=(Complex& a, float b) 
{
    a.re /= b;
    a.im /= b;
    return a;
}

Complex operator+(Complex a) 
{
    return a;
}

Complex operator-(Complex a) 
{
    Complex result;
    result.re = -a.re;
    result.im = -a.im;
    return result;
}

Complex operator*(Complex a) 
{
    Complex result = {};
    result.re =  a.re;
    result.im = -a.im;
    return result;
}

std::ostream& operator<<(std::ostream& out, Complex a) 
{
    if (a.re != 0)
        out << a.re;

    if (a.im > 0)
    {
        if (a.im != 1.0)
            out << " + " << a.im << "i";
        else
            out << " + i";
    }
    else if (a.im < 0) 
    {
        if (a.im != -1.0)
            out << " - " << -a.im << "i";
        else
            out << " - i";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Complex& c) 
{
    in >> c.re >> c.im;
    return in;
}

Complex exp(const Complex& a) 
{
    Complex result;
    result.re = std::exp(a.re) * std::cos(a.im);
    result.im = std::exp(a.re) * std::sin(a.im);
    return result;
}

Complex sin(const Complex& a) 
{
    Complex result;
    result.re = std::sin(a.re) * std::cosh(a.im);
    result.im = std::cos(a.re) * std::sinh(a.im);
    return result;
}

Complex cos(const Complex& a) 
{
    Complex result;
    result.re = std::cos(a.re) * std::cosh(a.im);
    result.im = std::sin(a.re) * std::sinh(a.im);
    return result;
}