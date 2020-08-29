#include <iostream>


// 产品类
class House {
private:
    std::string floor;
    std::string wall;
    std::string roof;

public:
    void setFloor(std::string floor) {
        this->floor = floor;
    }
    void setWall(std::string wall) {
        this->wall = wall;
    }
    void setRoof(std::string roof) {
        this->roof = roof;
    }
    void printInfo() {
        std::cout << "Include: "<< this->floor << " " << this->wall << " " << this->roof << std::endl;
    }
};

// 抽象建造者
class AbstractBuilder{
public:
    virtual ~AbstractBuilder(){}
    virtual void buildFloor() const = 0;
    virtual void buildWall() const = 0;
    virtual void buildRoof() const = 0;
};

// 具体建造者A
class ConcreteBuilderA: public AbstractBuilder{
private:
    House* house;

public:
    ConcreteBuilderA() {
        std::cout << "ConcreteBuilderA" << std::endl;
        house = new House();
    }
    ~ConcreteBuilderA() {
        delete house;
    }
    void buildFloor() const override {
        this->house->setFloor("FloorA");
    }
    void buildWall() const override {
        this->house->setWall("WallA");
    }
    void buildRoof() const override {
        this->house->setRoof("RoofA");
    }
    House* getHouse() {
        return this->house;
    }

};

// 具体建造者B
class ConcreteBuilderB: public AbstractBuilder{
private:
    House* house;

public:
    ConcreteBuilderB() {
        std::cout << "ConcreteBuilderB" << std::endl;
        house = new House();
    }
    ~ConcreteBuilderB() {
        delete house;
    }
    void buildFloor() const override {
        this->house->setFloor("FloorB");
    }
    void buildWall() const override {
        this->house->setWall("WallB");
    }
    void buildRoof() const override {
        this->house->setRoof("RoofB");
    }
    House* getHouse() {
        return this->house;
    }

};

// 主管类(指挥者类)
class Director {
private:
    AbstractBuilder* builder;

public:
    void setBuilder(AbstractBuilder* builder) {
        this->builder = builder;
    }
    void buildHouse() {
        this->builder->buildFloor();
        this->builder->buildWall();
        this->builder->buildRoof();
    }
};


int main(int argc, char * argv[]) {
    // 抽象建造者

    // 主管
    Director* director = new Director();
    // 产品
    House* house = nullptr;

    // 指定具体建造者A
    auto builderA = new ConcreteBuilderA();
    director->setBuilder(builderA);
    director->buildHouse();
    house = builderA->getHouse();
    house->printInfo();
    delete builderA;
    std::cout << std::endl;

    // 指定具体建造者B
    auto builderB = new ConcreteBuilderB();
    director->setBuilder(builderB);
    director->buildHouse();
    house = builderB->getHouse();
    house->printInfo();
    delete builderB;

    delete director;

    return 0;
}