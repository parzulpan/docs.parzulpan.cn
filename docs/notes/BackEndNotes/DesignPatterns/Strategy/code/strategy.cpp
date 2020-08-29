#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

// 策略接口类
class Strategy {
public:
    virtual ~Strategy() {}
    virtual std::string doAlgorithm(const std::vector<std::string> &data) const = 0;
    
};

// 上下文类
class Context {
private:
    Strategy *strategy_;

public:
    Context(Strategy *strategy = nullptr): strategy_(strategy){}
    // ~Context() {
    //     delete this->strategy_;
    // }
    void setStrategy(Strategy *strategy) {
        // delete this->strategy_;
        this->strategy_ = strategy;
    }
    void doSomeBusinessLogic() const {
        // ...
        std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
        std::string result = this->strategy_->doAlgorithm(std::vector<std::string>{"a", "e", "c", "b", "d"});
        std::cout << result << std::endl;
        // ...
    }
};

// 策略A类
class ConcreteStrategyA: public Strategy {
public:
    std::string doAlgorithm(const std::vector<std::string> &data) const override {
        std::string result;
        std::for_each(std::begin(data), std::end(data), [&result](const std::string &letter) {
            result += letter;
        });

        // 升序
        std::sort(std::begin(result), std::end(result));

        return result;
    }
};

// 策略B类
class ConcreteStrategyB: public Strategy {
public:
    std::string doAlgorithm(const std::vector<std::string> &data) const override {
        std::string result;
        for(const auto letter: data) {
            result += letter;
        }

        // 降序
        std::sort(std::rbegin(result), std::rend(result));

        return result;
    }
};


// 客户端
void ClientCode() {
    std::shared_ptr<Context> context = std::make_shared<Context>(new ConcreteStrategyA);
    // std::shared_ptr<Context> context(new Context(new ConcreteStrategyA));
    // Context *context = new Context(new ConcreteStrategyA);

    std::cout << "Client: Strategy is set to normal sorting." << std::endl;
    context->doSomeBusinessLogic();
    std::cout << context.use_count() << std::endl;
    std::cout << std::endl;


    std::cout << "Client: Strategy is set to reverse sorting." << std::endl;
    context->setStrategy(new ConcreteStrategyB);
    context->doSomeBusinessLogic();
    std::cout << context.use_count() << std::endl;

    // delete context;
}

int main(int argc, char *argv[]) {
    ClientCode();

    return 0;
}