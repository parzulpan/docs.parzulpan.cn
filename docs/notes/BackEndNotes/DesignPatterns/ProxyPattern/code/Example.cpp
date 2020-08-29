#include <iostream>
#include <string>
#include <ctime>


class Subject {
public:
    virtual ~Subject() {}
    virtual void method() const = 0;
};

class RealSubject: public Subject {
public:
    void method() const override {
        std::cout << "RealSubject: 调用业务方法。\n";
    }
};

class Log {
public:
    std::string getTime() const {
        time_t t = time(nullptr);
        // std::cout << "当前调用时间：" << asctime(localtime(&t)) << std::endl;
        return asctime(localtime(&t));
    }
};

class Proxy: public Subject {
private:
    RealSubject *real_subject_;
    Log *log_;
    void preCallMethod() const {
        std::cout << "method()被调用，当前调用时间：" << log_->getTime() << std::endl;
    }
    void postCallMethod() const {
        std::cout << "method()调用成功." << std::endl;
    }

public:
    Proxy() {
        real_subject_ = new RealSubject();
        log_ = new Log();
    }
    ~Proxy() {
        delete real_subject_;
        delete log_;
    }
    void method() const override {
        this->preCallMethod();
        this->real_subject_->method();
        this->postCallMethod();
    }
};

int main(int argc, char *argv[]) {
    Subject *subject = new Proxy();
    subject->method();

    delete subject;
    
    return 0;
}