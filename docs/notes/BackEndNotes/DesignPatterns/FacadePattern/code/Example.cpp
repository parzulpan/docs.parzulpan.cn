#include <iostream>
#include <memory>

//子系统：内存
class Memory
{
public:
    void selfCheck()
    {
        std::cout << "…………内存自检……\n";
    }
};

//子系统：CPU
class CPU
{
public:
    void run()
    {
        std::cout << "…………运行CPU运行……\n";
    }
};

//子系统：硬盘
class HardDisk
{
public:
    void read()
    {
        std::cout << "…………读取硬盘……\n";
    }
};

//子系统：操作系统
class OS
{
public:
    void load()
    {
        std::cout << "…………载入操作系统……\n";
    }
};

//外观类
class Facade
{
private:
    Memory *memory;
    CPU *cpu;
    HardDisk *hardDisk;
    OS *os;

public:
    Facade()
    {
        memory = new Memory();
        cpu = new CPU();
        hardDisk = new HardDisk();
        os = new OS();
    }
    void powerOn()
    {
        std::cout << "正在开机……\n";
        memory->selfCheck();
        cpu->run();
        hardDisk->read();
        os->load();
        std::cout << "开机完成……\n";
    }
};

int main(int argc, char *argv[])
{
    std::shared_ptr<Facade> facade = std::make_shared<Facade>();
    facade->powerOn();

    return 0;
}