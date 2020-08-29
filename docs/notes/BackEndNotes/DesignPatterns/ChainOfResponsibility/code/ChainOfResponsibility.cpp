#include <iostream>
#include <string>
#include <vector>

class Handler {
public:
    virtual ~Handler() {}
    virtual Handler *setNext(Handler *handler) = 0;
    virtual std::string Handle(std::string request) = 0;
};

class AbstractHandler : public Handler {
private:
    Handler *next_handler_;

public:
    AbstractHandler() : next_handler_(nullptr) {}
    Handler *setNext(Handler *handler) override {
        this->next_handler_ = handler;
        return handler;
    }
    std::string Handle(std::string request) override {
        if( this->next_handler_ ) {
            return this->next_handler_->Handle(request);
        }
        return {};
    }
 };

class ConcreteHandlerA: public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if(request == "A") {
            return "A: 我 能 处 理 它 " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);
        }
    }
};

class ConcreteHandlerB: public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if(request == "B") {
            return "B: 我 能 处 理 它 " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);
        }
    }
};

class ConcreteHandlerC: public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if(request == "C") {
            return "C: 我 能 处 理 它 " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);
        }
    }
};

void ClientCode(Handler &handler) {
    std::vector<std::string> request = {"B", "A", "D"};
    for(const std::string &r: request) {
        std::cout << "Client: 谁 能 处 理 "  << r << " ？\n";
        const std::string result = handler.Handle(r);
        if(!result.empty()) {
            std::cout << " " << result;
        } else {
            std::cout << " " << r << ": 不 能 被 处 理！\n";
        }
    }
}

int main(int argc, char *argv[]) {
    ConcreteHandlerA *a = new ConcreteHandlerA;
    ConcreteHandlerB *b = new ConcreteHandlerB;
    ConcreteHandlerC *c = new ConcreteHandlerC;
    a->setNext(b)->setNext(c);

    std::cout << "Chain: A > B > C\n";
    ClientCode(*a);
    std::cout << "\n";

    std::cout << "Chain: B > C\n";
    ClientCode(*b);

    delete a;
    delete b;
    delete c;

    return 0;
}