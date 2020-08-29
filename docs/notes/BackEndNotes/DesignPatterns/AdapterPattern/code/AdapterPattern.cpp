#include <iostream>
#include <string>
#include <algorithm>

// 目标抽象类：定义客户所需要的接口
class Target {
public:
    virtual ~Target() = default;
    virtual std::string Request() const {
        return "Target: The default target`s behavior.";
    }
};

// 适配者类
class Adaptee {
public:
    std::string SpecificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

// 适配器类
class Adapter: public Target {
private:
    Adaptee *adaptee_;

public:
    Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}
    std::string Request() const override {
        std::string to_reverse = this->adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};

// 客户端
void ClientCode(const Target* target) {
    std::cout << target->Request();
}

int main(int argc, char *argv[]) {
    std::cout << "Client: 处理任何数据" << std::endl;
    Target* target = new Target;
    ClientCode(target);
    std::cout << std::endl << std::endl;

    std::cout << "Client: 我不能理解这个数据" << std::endl;
    Adaptee* adaptee = new Adaptee;
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << std::endl << std::endl;

    std::cout << "Client: 结合适配器可以理解这个数据" << std::endl;
    Adapter *adapter = new Adapter(adaptee);
    ClientCode(adapter);
    std::cout << std::endl << std::endl;

    delete target;
    delete adaptee;
    delete adapter;

    return 0;
}