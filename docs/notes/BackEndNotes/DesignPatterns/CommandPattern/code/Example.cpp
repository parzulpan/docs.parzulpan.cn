#include <iostream>
#include <string>


// 接收者：电灯类
class Lamp {
private:
    bool lampState_;

public:
    Lamp() {
        this->lampState_ = false;
    }
    void on() {
        lampState_ = true;
        std::cout << "电灯已开启！\n";
    }
    void off() {
        lampState_ = false;
        std::cout << "电灯已关闭！\n";
    }
    bool getLampState() const {
        return lampState_;
    }
};

// 接收者：空调类
class Air {
private:
    bool airState_;

public:
    Air() {
        this->airState_ = false;
    }
    void on() {
        airState_ = true;
        std::cout << "空调已开启！\n";
    }
    void off() {
        airState_ = false;
        std::cout << "空调已关闭！\n";
    }
    bool getAirState() const {
        return airState_;
    }
};

// 抽象命令类
class Command {
private:
    Command *command;

public:
    virtual ~Command() {}
    virtual void execute() const = 0;
};

// 具体命令类
class LampCommand : public Command {
private:
    Lamp *lamp;

public:
    LampCommand() {
        std::cout << "开发控制电灯！\n";
        lamp = new Lamp();
    }
    ~LampCommand() {
        delete lamp;
    }
    void execute() const override {
        if(lamp->getLampState()) {
            lamp->off();
        } else {
            lamp->on();
        }
    }
};

// 具体命令类
class AirCommand : public Command {
private:
    Air *air;

public:
    AirCommand() {
        std::cout << "开发控制空调！\n";
        air = new Air();
    }
    ~AirCommand() {
        delete air;
    }
    void execute() const override {
        if(air->getAirState()) {
            air->off();
        } else {
            air->on();
        }
    }
};

// 调用者：按钮类
class Button {
private:
    Command *command_;

public:
    void setCommand(Command *command) {
        this->command_ = command;
    }
    void click() const {
        std::cout << "点击开关：";
        command_->execute();
    }
};


int main(int argc, char * argv[]) {
    Button * button = new Button;

    // 按钮控制电灯
    Command *lampCommand = new LampCommand();
    button->setCommand(lampCommand);
    button->click();
    button->click();
    button->click();
    button->click();
    std::cout << "\n";

    // 按钮控制空调
    Command *airCommand = new AirCommand();
    button->setCommand(airCommand);
    button->click();
    button->click();
    button->click();

    delete button;

    return 0;
}