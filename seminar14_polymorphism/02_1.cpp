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

std::vector<Individual*> createIndividuals() {
    std::vector<Individual*> individuals;
    for (int i = 0; i < 3; ++i) {individuals.push_back(new Alice());}
    for (int i = 0; i < 2; ++i) {individuals.push_back(new Bob());}
    for (int i = 0; i < 4; ++i) {individuals.push_back(new Casper());}
    return individuals;
}

void letThemSpeak(const std::vector<Individual*>& individuals) {
    for (const Individual* p : individuals) {
        if (p != nullptr) {p->speak();}
    }
}

void deleteIndividuals(std::vector<Individual*>& individuals) {
    for (Individual* p : individuals) {delete p;}
    individuals.clear();
}

int identification_vmethod(const Individual* p) {return -1;}

int identification_dynamic(const Individual* p) {
    if (dynamic_cast<const Alice*>(p))   return 0;
    if (dynamic_cast<const Bob*>(p))     return 1;
    if (dynamic_cast<const Casper*>(p))  return 2;
    return -1;
}

int identification_typeid(const Individual* p) {
    if (p == nullptr) return -1;
    
    if (typeid(*p) == typeid(Alice))  return 0;
    if (typeid(*p) == typeid(Bob))    return 1;
    if (typeid(*p) == typeid(Casper)) return 2;
    return -1;
}

int main() {
    std::vector<Individual*> vec = createIndividuals();
    letThemSpeak(vec);
    if (!vec.empty()) {
        std::cout << "Identification (dynamic_cast):" << identification_dynamic(vec[0]) << std::endl;
        std::cout << "Identification (typeid):" << identification_typeid(vec[0]) << std::endl;
    }
    deleteIndividuals(vec);
}