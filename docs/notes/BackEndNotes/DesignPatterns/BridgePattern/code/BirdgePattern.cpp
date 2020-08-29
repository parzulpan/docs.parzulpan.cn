#include <iostream>
#include <string>

// 实现部分(实现类接口)
class Implementation {
public:
    virtual ~Implementation() {}
    virtual std::string OperationImplementation() const = 0;
};

// 具体实现
class ConcreteImplementationA : public Implementation {
public:
    std::string OperationImplementation() const override { 
        return "ConcreteImplementationA: 这是平台A上的结果.\n";
    }
};

// 具体实现
class ConcreteImplementationB : public Implementation {
public:
    std::string OperationImplementation() const override { 
        return "ConcreteImplementationB: 这是平台B上的结果.\n";
    }
};

// 抽象部分(抽象类)
class Abstraction {
protected:
    Implementation* implementation_;

public:
    Abstraction(Implementation* implementation) : implementation_(implementation) {}
    virtual ~Abstraction() {}
    virtual std::string Operation() const {
        return "Abstraction: Base operation with:\n" +
           this->implementation_->OperationImplementation();
    }
};

// 精确抽象(扩展抽象类)
class ExtendedAbstraction: public Abstraction {
public:
    ExtendedAbstraction(Implementation* implementation): Abstraction(implementation) {}
    std::string Operation() const override {
        return "ExtendedAbstraction: Extended operation with:\n" +
           this->implementation_->OperationImplementation();
    }
};

void ClientCode(const Abstraction& abstraction) {
    // ...
    std::cout << abstraction.Operation();
    // ...
}

int main(int argc, char *argv[]) {
    Implementation* implementation = new ConcreteImplementationA;
    Abstraction* abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    std::cout << std::endl;
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);
    delete implementation;
    delete abstraction;

    return 0;
}