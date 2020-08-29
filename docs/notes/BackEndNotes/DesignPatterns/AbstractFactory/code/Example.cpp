#include <iostream>

class AbstractBall {
public:
    virtual ~AbstractBall() {}
    virtual void play() const = 0;
};

class Basketball: public AbstractBall {
public:
    Basketball() {
        play();
    }
    void play() const override {
        std::cout << "play basketball." << std::endl;
    }
};

class Football: public AbstractBall {
public:
    Football() {
        play();
    }
    void play() const override {
        std::cout << "play football." << std::endl;
    }
};

class AbstractShirt {
public:
    virtual ~AbstractShirt() {}
    virtual void wear() const = 0;
};

class BasketballShirt: public AbstractShirt {
public:
    BasketballShirt() {
        wear();
    }
    void wear() const override {
        std::cout << "wear basketball shirt." << std::endl;
    }
};

class FootballShirt: public AbstractShirt {
public:
    FootballShirt() {
        wear();
    }
    void wear() const override {
        std::cout << "wear football shirt." << std::endl;
    }
};

class AbstractFactory {
public:
    virtual AbstractBall* getBall() const = 0;
    virtual AbstractShirt* getShirt() const = 0;
};

class BasketballFactory: public AbstractFactory {
public:
    AbstractBall* getBall() const override {
        std::cout << "get basketball." << std::endl;
        return new Basketball();
    }
    AbstractShirt* getShirt() const override {
        std::cout << "get basketball shirt." << std::endl;
        return new BasketballShirt();
    }
};

class FootballFactory: public AbstractFactory {
public:
    AbstractBall* getBall() const override {
        std::cout << "get football." << std::endl;
        return new Football();
    }
    AbstractShirt* getShirt() const override {
        std::cout << "get football shirt." << std::endl;
        return new FootballShirt();
    }
};


int main(int argc, char * argv[]) {
    AbstractFactory* fac = nullptr;
    AbstractBall* ball = nullptr;
    AbstractShirt* shirt = nullptr;

    fac = new BasketballFactory();
    ball = fac->getBall();
    shirt = fac->getShirt();
    std::cout << std::endl;

    fac = new FootballFactory();
    ball = fac->getBall();
    shirt = fac->getShirt();
    std::cout << std::endl;

    delete fac;
    delete ball;
    delete shirt;

    return 0;
}