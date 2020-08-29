#include <iostream>

// 抽象主题角色类
class Subject {
public:
    virtual ~Subject() {}
    virtual void Request() const = 0;
};

// 真实主题角色类
class RealSubject : public Subject {
public:
    void Request() const override {
        std::cout << "RealSubject: 处理要求.\n";
    }
};

// 代理主题角色类
class Proxy: public Subject {
private:
    RealSubject *real_subject_;
    bool checkAccess() const {
        std::cout << "Proxy:在发出真实请求之前检查访问权限。\n";
        return true;
    }
    void logAccess() const {
        std::cout << "Proxy: 记录请求时间。\n";
    }

public:
    Proxy(RealSubject* real_subject) : real_subject_(new RealSubject(*real_subject)) {}
    ~Proxy() {
        delete real_subject_;
    }
    void Request() const override {
        if(this->checkAccess()) {
            this->real_subject_->Request();
            this->logAccess();
        }
    }
};


void ClientCode(const Subject& subject) {
    // ...
    subject.Request();
    // ...
}


int main(int argc, char * argv[]) {
    std::cout << "Client: 执行真实角色:\n";
    RealSubject *real_subject = new RealSubject;
    ClientCode(*real_subject);
    std::cout << "\n";

    std::cout << "Client: 执行代理角色:\n";
    Proxy *proxy = new Proxy(real_subject);
    ClientCode(*proxy);

    delete real_subject;
    delete proxy;

    return 0;

}
