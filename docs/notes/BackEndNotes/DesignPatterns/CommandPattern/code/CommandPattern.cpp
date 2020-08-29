#include <iostream>
#include <string>

class Receiver {
 public:
    void DoSomething(const std::string &a) {
        std::cout << "Receiver: 工作在 (" << a << ".)\n";
    }
    void DoSomethingElse(const std::string &b) {
        std::cout << "Receiver: 也工作在 (" << b << ".)\n";
    }
};

class Command {
public:
    virtual ~Command() {}
    virtual void Execute() const = 0;
};

class SimpleCommand : public Command {
private:
    std::string pay_load_;

public:
    explicit SimpleCommand(std::string pay_load) : pay_load_(pay_load) {}
    void Execute() const override {
        std::cout << "SimpleCommand: 自己做一些简单的事情 (" << this->pay_load_ << ")\n"; 
    }
};

class ComplexCommand : public Command {
private:
    Receiver *receiver_;
    std::string a_;
    std::string b_;

public:
    ComplexCommand(Receiver *receiver, std::string a, std::string b) : receiver_(receiver), a_(a), b_(b) {}
    void Execute() const override {
        std::cout << "ComplexCommand: 由接收者对象完成一些负责的事情 \n";
        this->receiver_->DoSomething(this->a_);
        this->receiver_->DoSomethingElse(this->b_);
    }
};


class Invoker {
private:
    Command *on_start_;
    Command *on_finish_;

public:
    ~Invoker() {
        delete on_start_;
        delete on_finish_;
    }
    void setOnStart(Command *command) {
        this->on_start_ = command;
    }
    void setOnFinish(Command *command) {
        this->on_finish_ = command;
    }
    void DoSomethingImportant() {
        std::cout << "Invoker: 开始！\n";
        if(this->on_start_) {
            this->on_start_->Execute();
        }
        std::cout << "Invoker: 中途！\n";
        std::cout << "Invoker: 完成！\n";
        if(this->on_finish_) {
            this->on_finish_->Execute();
        }
    }
};


int main(int argc, char * argv[]) {
    Invoker *invoker = new Invoker;
    invoker->setOnStart(new SimpleCommand("你好！"));
    Receiver *receiver = new Receiver;
    invoker->setOnFinish(new ComplexCommand(receiver, "发送邮件！", "准备回报材料！"));
    invoker->DoSomethingImportant();

    delete invoker;
    delete receiver;

    return 0;
}