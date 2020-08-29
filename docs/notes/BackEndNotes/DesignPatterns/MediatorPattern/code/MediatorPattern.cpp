#include <iostream>
#include <string>
#include <memory>


class BaseComponent;

// 中介者
class Mediator {
public:
    virtual ~Mediator() {}
    virtual void Notify(BaseComponent *sender, std::string event) const = 0;
};

// 基础组件
class BaseComponent {
protected:
    Mediator *m_mediator;

public:
    BaseComponent(Mediator *mediator = nullptr) :m_mediator(mediator) {}
    virtual ~BaseComponent() {}
    void setMediator(Mediator *mediator) {
        this->m_mediator = mediator;
    }
};

// 具体组件
class Component1: public BaseComponent {
public:
    void doA() {
        std::cout << "Component1 doss A.\n";
        this->m_mediator->Notify(this, "A");
    }
    void doB() {
        std::cout << "Component1 doss B.\n";
        this->m_mediator->Notify(this, "B");
    }
};

// 具体组件
class Component2: public BaseComponent {
public:
    void doC() {
        std::cout << "Component1 doss C.\n";
        this->m_mediator->Notify(this, "C");
    }
    void doD() {
        std::cout << "Component1 doss D.\n";
        this->m_mediator->Notify(this, "D");
    }
};

class ConcreteMediator : public Mediator {
private:
    std::shared_ptr<Component1> m_component1;
    std::shared_ptr<Component2> m_component2;

public:
    ConcreteMediator(std::shared_ptr<Component1> component1, std::shared_ptr<Component2> component2) : m_component1(component1), m_component2(component2) {
        this->m_component1->setMediator(this);
        this->m_component2->setMediator(this);
    }
    void Notify(BaseComponent *sender, std::string event) const override {
        if(event == "A") {
            std::cout << "中介者对A做出反应并触发以下操作：\n";
            this->m_component2->doC();
        }
        if(event == "D") {
            std::cout << "中介者对D做出反应并触发以下操作：\n";
            this->m_component1->doB();
            this->m_component2->doC();
        }
    }
};


int main(int argc, char * argv[]) {
    std::shared_ptr<Component1> c1 = std::make_shared<Component1>();
    std::shared_ptr<Component2> c2 = std::make_shared<Component2>();
    std::shared_ptr<ConcreteMediator> mediator = std::make_shared<ConcreteMediator>(c1, c2);

    std::cout << "Client：触发A操作：\n";
    c1->doA();
    std::cout << "\n";

    std::cout << "Client：触发D操作：\n";
    c2->doD();

    return 0;
}