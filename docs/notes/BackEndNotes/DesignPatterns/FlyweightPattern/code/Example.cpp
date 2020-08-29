#include <iostream>
#include <string>
#include <mutex>
#include <vector>

// 抽象享元类
class NetDevice{
public:
    virtual ~NetDevice() {}
    virtual std::string getName() const = 0;
    void printName() {
        std::cout << "NetDevice: " << getName() << std::endl;
    }
};

// 具体享元类：集线器
class Hub: public NetDevice {
public:
    std::string getName() const override {
        return "集线器";
    }
};

// 具体享元类：交换机
class Switch: public NetDevice {
public:
    std::string getName() const override {
        return "交换机";
    }
};

// 享元工厂类，使用单例模式，保证工厂实例的唯一性
class NetDeviceFactory {
private:
    // 单例
    static NetDeviceFactory* instance;
    static std::mutex m_mutex;

    // 共享池
    std::vector<NetDevice*> devicePool;

    NetDeviceFactory() {
        devicePool.push_back(new Hub());
        devicePool.push_back(new Switch());
    }

public:
    NetDevice* getNetDevice(const std::string& name) {
        if(name == "集线器") {
            return devicePool[0];
        } else if(name == "交换机") {
            return devicePool[1];
        } else {
            std::cout << "Error" << std::endl;
            return nullptr;
        }
    }

    static NetDeviceFactory* getInstance() {
        if(instance == nullptr) {
            m_mutex.lock();
            if(instance == nullptr) {
                instance = new NetDeviceFactory();
            }
            m_mutex.unlock();
        }
        return instance;
    }
};

NetDeviceFactory* NetDeviceFactory::instance = nullptr;
std::mutex NetDeviceFactory::m_mutex;


int main(int argc, char *argv[]) {
    NetDeviceFactory *factory = NetDeviceFactory::getInstance();
    NetDevice *device1, *device2, *device3, *device4;

    device1 = factory->getNetDevice("集线器");
    device1->printName();
    device2 = factory->getNetDevice("集线器");
    device2->printName();
    std::cout << "两个集线器是否为同一个？" << std::endl;
    std::cout << "device1: " << device1 << std::endl;
    std::cout << "device1: " << device2 << std::endl;
    std::cout << std::endl;

    device3 = factory->getNetDevice("交换机");
    device3->printName();
    device4 = factory->getNetDevice("交换机");
    device4->printName();
    std::cout << "两个交换机是否为同一个？" << std::endl;
    std::cout << "device3: " << device3 << std::endl;
    std::cout << "device4: " << device4 << std::endl;

    return 0;
}