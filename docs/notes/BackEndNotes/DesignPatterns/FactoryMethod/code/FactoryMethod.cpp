#include <iostream>
#include <memory>

class Product {
public:
    virtual ~Product() {}    // virtual
    virtual std::string Operation() const = 0;
};

class ConceteProduct1: public Product {
public:
    std::string Operation() const override {
        return "{Result of the ConcreteProduct1}";
    }
};

class ConceteProduct2: public Product {
public:
    std::string Operation() const override {
        return "{Result of the ConcreteProduct2}";
    }
};

class Creator {
public:
    virtual ~Creator() {}   // virtual
    virtual Product* FactoryMethod() const = 0;
    std::string SomeOperation() const {
        Product* product = this->FactoryMethod();
        std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
        delete product;
        return result;
    }

};

class ConcreteCreator1: public Creator {
public:
    Product* FactoryMethod() const override {
        return new ConceteProduct1();
    }
};

class ConcreteCreator2: public Creator {
public:
    Product* FactoryMethod() const override {
        return new ConceteProduct2();
    }
};

void ClientCode(const Creator& creator) {
    // ...
    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n" << creator.SomeOperation() << std::endl;
    // ...
}

int main(int argc, char *argv[]) {
    std::cout << "App: Launched with the ConcreteCreator1.\n";
    // Creator* creator = new ConcreteCreator1();
    std::shared_ptr<Creator> creator = std::make_shared<ConcreteCreator1>();
    ClientCode(*creator);
    std::cout << std::endl;

    std::cout << "App: Launched with the ConcreteCreator2.\n";
    // Creator* creator = new ConcreteCreator2();
    std::shared_ptr<Creator> creator2 = std::make_shared<ConcreteCreator2>();
    ClientCode(*creator2);
    std::cout << std::endl;

    return 0;
}