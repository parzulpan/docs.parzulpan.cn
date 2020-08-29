#include <iostream>


// 实现类接口
class Game {
public:
    virtual ~Game() {}
    virtual void play() const = 0;
};

// 具体实现类GmaeA
class GameA: public Game {
public:
    void play() const override {
        std::cout << "玩游戏A" << std::endl;
    }
};

// 具体实现类GmaeB
class GameB: public Game {
public:
    void play() const override {
        std::cout << "玩游戏B" << std::endl;
    }
};

// 抽象类Phone
class Phone {
private:
    Game *game;

public:
    virtual ~Phone() {}
    virtual void run(Game *game) = 0;
    virtual void play() const = 0;
};

// 扩充抽象类PhoneA
class PhoneA : public Phone {
private:
    Game *game;

public:
    void run(Game *game) override {
        this->game = game;
    }
    void play() const override {
        this->game->play();
    }
};


int main(int argc, char *argv[]) {
    Phone *phone = new PhoneA;

    Game *game = new GameA;
    phone->run(game);
    phone->play();
    delete game;

    game = new GameB;
    phone->run(game);
    phone->play();
    delete game;

    delete phone;

    return 0;

}