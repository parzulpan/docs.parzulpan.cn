#include <iostream>


class AbstractProductA {
public:
    virtual ~AbstractProductA() {};
    virtual std::string usefulFuncA() const = 0;
};

class ConcreteProductA1: public AbstractProductA {
public:
    std::string usefulFuncA() const override {
        return "The result of the product A1.";
    }
};

class ConcreteProductA2: public AbstractProductA {
public:
    std::string usefulFuncA() const override {
        return "The result of the product A2.";
    }
};

class AbstractProductB {
public:
    virtual ~AbstractProductB() {};
    virtual std::string usefulFuncB() const = 0;
    virtual std::string anotherUsefulFuncB(const AbstractProductA& collaborator) const = 0;
};

class ConcreteProductB1: public AbstractProductB {
public:
    std::string usefulFuncB() const override {
        return "The result of the product B1.";
    }
    std::string anotherUsefulFuncB(const AbstractProductA& collaborator) const override {
        const std::string result = collaborator.usefulFuncA();
        return "The result of the B1 collaborating with ( " + result + " )";
    }
};

class ConcreteProductB2: public AbstractProductB {
public:
    std::string usefulFuncB() const override {
        return "The result of the product B2.";
    }
    std::string anotherUsefulFuncB(const AbstractProductA& collaborator) const override {
        const std::string result = collaborator.usefulFuncA();
        return "The result of the B2 collaborating with ( " + result + " )";
    }
};

class AbstractFactory {
public:
    virtual AbstractProductA* CreateProductA() const  = 0;
    virtual AbstractProductB* CreateProductB() const  = 0;
};

class ConcreteFactory1 : public AbstractFactory {
public:
    AbstractProductA* CreateProductA() const override {
        return new ConcreteProductA1();
    }
    AbstractProductB* CreateProductB() const override {
        return new ConcreteProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory {
public:
    AbstractProductA* CreateProductA() const override {
        return new ConcreteProductA2();
    }
    AbstractProductB* CreateProductB() const override {
        return new ConcreteProductB2();
    }
};

void ClientCode(const AbstractFactory& factory) {
    const AbstractProductA* proA = factory.CreateProductA();
    const AbstractProductB* proB = factory.CreateProductB();
    std::cout << proB->usefulFuncB() << std::endl;
    std::cout << proB->anotherUsefulFuncB(*proA) << std::endl;
    delete proA;
    delete proB;
}

int main(int argc, char* argv[]) {
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1 *f1 = new ConcreteFactory1();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    ConcreteFactory2 *f2 = new ConcreteFactory2();
    ClientCode(*f2);
    delete f2;
    return 0;
}