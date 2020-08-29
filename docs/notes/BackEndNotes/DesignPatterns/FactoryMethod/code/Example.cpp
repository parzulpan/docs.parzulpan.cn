#include <iostream>


// 抽象产品类
class AbstractSportProduct {
public:
    virtual ~AbstractSportProduct() {}
    virtual void printName() const = 0;
    virtual void play() const = 0;
};

// 具体产品类
class Basketball: public AbstractSportProduct {
public:
    Basketball() {
        printName();
        play();
    }
    void printName() const {
        std::cout << "get Basketball" << std::endl;
    }
    void play() const {
        std::cout << "play Basketball" << std::endl;
    }
};

// 具体产品类
class Football: public AbstractSportProduct {
public:
    Football() {
        printName();
        play();
    }
    void printName() const {
        std::cout << "get Football" << std::endl;
    }
    void play() const {
        std::cout << "play Football" << std::endl;
    }
};

// 具体产品类
class Volleyball: public AbstractSportProduct {
public:
    Volleyball() {
        printName();
        play();
    }
    void printName() const {
        std::cout << "get Volleyball" << std::endl;
    }
    void play() const {
        std::cout << "play Volleyball" << std::endl;
    }
};

// 抽象工厂类
class AbstractFactory {
public:
    virtual ~AbstractFactory() {}
    virtual AbstractSportProduct *getSportProduct() const  = 0;
};

// 具体工厂类
class BasketballFactory : public AbstractFactory {
public:
    BasketballFactory() {
        // ...
    }
    AbstractSportProduct* getSportProduct() const {
        std::cout << "basketball" << std::endl;
        return new Basketball();
    }
};

// 具体工厂类
class FootballFactory : public AbstractFactory {
public:
    FootballFactory() {
        // ...
    }
    AbstractSportProduct* getSportProduct() const {
        std::cout << "football" << std::endl;
        return new Football();
    }
};

// 具体工厂类
class VolleyballFactory : public AbstractFactory {
public:
    VolleyballFactory() {
        // ...
    }
    AbstractSportProduct* getSportProduct() const {
        std::cout << "volleyball" << std::endl;
        return new Volleyball();
    }
};


int main(int argc, char* argv[]) {
    AbstractFactory* fac = nullptr;
    AbstractSportProduct* pro = nullptr;

    fac = new BasketballFactory();
    pro = fac->getSportProduct();
    std::cout << std::endl;

    fac = new FootballFactory();
    pro = fac->getSportProduct();
    std::cout << std::endl;

    fac = new VolleyballFactory();
    pro = fac->getSportProduct();
    std::cout << std::endl;

    delete fac;
    delete pro;

    return 0;
}