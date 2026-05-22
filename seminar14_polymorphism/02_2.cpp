#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>

class Individual
{
public:
    virtual void speak() const = 0;
    virtual ~Individual() = default;
};

class Alice : public Individual
{
public:
    void speak() const override
    {
        std::cout << "Hi, I am Alice" << std::endl;
    }
};

class Bob : public Individual
{
public:
    void speak() const override
    {
        std::cout << "Hi, I am Bob" << std::endl;
    }
};

class Casper : public Individual
{
public:
    void speak() const override
    {
        std::cout << "Hi, I am Casper" << std::endl;
    }
};

std::vector<std::unique_ptr<Individual>> createIndividualsSmart() {
    std::vector<std::unique_ptr<Individual>> individuals;
    for (int i = 0; i < 3; ++i) individuals.push_back(std::make_unique<Alice>()); // [cite: 100]
    for (int i = 0; i < 2; ++i) individuals.push_back(std::make_unique<Bob>());   // [cite: 100]
    for (int i = 0; i < 4; ++i) individuals.push_back(std::make_unique<Casper>());// [cite: 100]
    return individuals;
}

void letThemSpeakSmart(const std::vector<std::unique_ptr<Individual>>& individuals) {
    for (const auto& p : individuals) {
        if (p) {p->speak();}
    }
}