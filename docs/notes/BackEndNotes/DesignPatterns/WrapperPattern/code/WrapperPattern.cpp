#include <iostream>


// 抽象部(构)件
class Component {
public:
    virtual ~Component() {}
    virtual std::string Operation() const = 0;
};

// 具体部(构)件
class ConcreteComponent : public Component {
public:
    std::string Operation() const override {
        return "ConcreteComponent";
    }
};

// 抽象装饰
class Decorator : public Component {
protected:
    Component* component_;

public:
    Decorator(Component* component) : component_(component) {}
    std::string Operation() const override {
        return this->component_->Operation();
    }
};

// 具体装饰A
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Component* component) : Decorator(component) {}
    std::string Operation() const override {
        return "ConcreteDecoratorA("  + Decorator::Operation()  + ")";
    }
};

// 具体装饰B
class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component* component) : Decorator(component) {}
    std::string Operation() const override {
        return "ConcreteDecoratorB("  + Decorator::Operation()  + ")";
    }
};

void ClientCode(Component* component) {
    // ...
    std::cout << "RESULT: " << component->Operation() << std::endl;
    // ...
}

int main(int argc, char *argv[]) {
    Component* simple = new ConcreteComponent;
    std::cout << "Client: I've got a simple component:\n";
    ClientCode(simple);
    std::cout << "\n";

    // 为simple装饰上ConcreteDecoratorA和ConcreteDecoratorB
    Component* decorator1 = new ConcreteDecoratorA(simple);
    Component* decorator2 = new ConcreteDecoratorB(decorator1);
    std::cout << "Client: Now I've got a decorated component:\n";
    ClientCode(decorator2);
    std::cout << "\n";

    delete simple;
    delete decorator1;
    delete decorator2;

    return 0;
}