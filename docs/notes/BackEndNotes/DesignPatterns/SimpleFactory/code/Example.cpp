#include <iostream>
#include <memory>

// 抽象产品类
class AbstractSportProduct {
public:
    virtual ~AbstractSportProduct(){}
    // 抽象方法
    virtual void printName() const = 0;
    virtual void play() const = 0;
};


// 具体产品类Basketball
class Basketball: public AbstractSportProduct {
public:
    Basketball(){
        printName();
        play();
    }
    // 具体实现
    void printName() const {
        std::cout << "get Basketball." << std::endl;
    }
    void play() const {
        std::cout << "play Basketball." << std::endl;
    }
};


// 具体产品类Football
class Football: public AbstractSportProduct {
public:
    Football(){
        printName();
        play();
    }
    // 具体实现
    void printName() const {
        std::cout << "get Football." << std::endl;
    }
    void play() const {
        std::cout << "play Football." << std::endl;
    }
};


// 具体产品类Volleyball
class Volleyball: public AbstractSportProduct {
public:
    Volleyball(){
        printName();
        play();
    }
    // 具体实现
    void printName() const {
        std::cout << "get Volleyball." << std::endl;
    }
    void play() const {
        std::cout << "play Volleyball." << std::endl;
    }
};


// 工厂类
class Factory {
public:
    AbstractSportProduct* getSportProduct(std::string productName) {
        AbstractSportProduct *pro = nullptr;
        if(productName == "Basketball") {
            pro = new Basketball();
        } else if(productName == "Football") {
            pro = new Football();
        } else if(productName == "Volleyball") {
            pro = new Volleyball();
        }
        return pro;
    }
};


int main(int argc, char *argv[]) {
    std::shared_ptr<Factory> fac = std::make_shared<Factory>();
    AbstractSportProduct *pro = nullptr;

    pro = fac->getSportProduct("Basketball");
    pro = fac->getSportProduct("Football");
    pro = fac->getSportProduct("Volleyball");

    return 0;
}