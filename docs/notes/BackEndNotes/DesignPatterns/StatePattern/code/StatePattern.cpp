#include <iostream>
#include <typeinfo>

// 上下文
class Context;

// 状态
class State {
protected:
    Context *m_context;

public:
    virtual ~State() {}
    void setContext(Context *context) {
        m_context = context;
    }
    virtual void handle1() = 0;
    virtual void handle2() = 0;
};

class Context {
private:
    State *m_state;

public:
    Context(State *state) : m_state(nullptr) {
        transitionTo(state);
    }
    ~Context() {
        delete m_state;
    }

    void transitionTo(State *state) {
        std::cout << "上下文：转换状态为 " << typeid(*state).name() << "\n";
        if(m_state != nullptr) {
            delete m_state;
        }
        m_state = state;
        m_state->setContext(this);
    }
    void request1() {
        m_state->handle1();
    }
    void request2() {
        m_state->handle2();
    }
};

// 具体状态
class ConcreteStateA: public State {
public:
    void handle1() override;
    void handle2() override {
        std::cout << "状态A：处理请求2。\n";
    }
};

// 具体状态
class ConcreteStateB: public State {
public:
    void handle1() override {
        std::cout << "状态B：处理请求1。\n";
    }
    void handle2() override {
        std::cout << "状态B：处理请求2。\n";
        std::cout << "状态B：想要更改上下文状态。\n";
        m_context->transitionTo(new ConcreteStateA);
    }
};

void ConcreteStateA::handle1() {
    std::cout << "状态A：处理请求1。\n";
        std::cout << "状态A：想要更改上下文状态。\n";
        m_context->transitionTo(new ConcreteStateB);
}

void ClientCode() {
    Context *context = new Context(new ConcreteStateA);
    context->request1();
    std::cout << "\n";
    context->request2();
    std::cout << "\n";
    context->request2();

    delete context;
}

int main(int argc, char *argv[]) {
    ClientCode();

    return 0;
}