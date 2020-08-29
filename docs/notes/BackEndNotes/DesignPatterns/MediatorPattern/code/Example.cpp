#include <iostream>
#include <string>
#include <vector>
#include <memory>

enum PERSON_TYPE {
    TENANT,
    LANDLORD
};

class BaseComponent;

class BaseMediator {
public:
    virtual ~BaseMediator() {}
    virtual void registerInfo(BaseComponent *component) = 0;
    virtual void getInfo(BaseComponent *component) = 0;
};

class BaseComponent {
protected:
    BaseMediator *m_mediator;
    PERSON_TYPE personType;

public:
    BaseComponent(BaseMediator *mediator = nullptr) : m_mediator(mediator) {}
    virtual ~BaseComponent() {}
    void setMediator(BaseMediator *mediator) {
        this->m_mediator = mediator;
    }
    virtual void ask() = 0;
    virtual void answer() = 0;
    virtual PERSON_TYPE getType() const = 0;
};

// 租户
class Tenant: public BaseComponent {
private:
    std::string m_name;
    std::string m_phoneNumber;

public:
    Tenant(const std::string& name = "NULL", const std::string& phoneNumber="NULL") : m_name(name), m_phoneNumber(phoneNumber) {
        personType = TENANT;
    }
    void ask() override {
        std::cout << "租户查看房东信息：\n";
        this->m_mediator->getInfo(this);
    }
    void answer() override {
        std::cout << "[租户信息] " << " 姓名：" << m_name << "\t" << " 电话：" << m_phoneNumber  << "\t" << "\n";
    }
    PERSON_TYPE getType() const override {
        return personType;
    }
};

// 房东
class Landlord: public BaseComponent {
private:
    std::string m_name;
    std::string m_phoneNumber;
    std::string m_address;
    std::string m_price;

public:
    Landlord(const std::string& name = "NULL", const std::string& phoneNumber="NULL", const std::string& address="NULL", const std::string& price="NULL") : m_name(name), m_phoneNumber(phoneNumber), m_address(address), m_price(price) {
        personType = LANDLORD;
    }
    void ask() override {
        std::cout << "房东查看租户信息：\n";
        this->m_mediator->getInfo(this);
    }
    void answer() override {
        std::cout << "[房东信息] " << " 姓名：" << m_name  << "\t" << " 电话：" << m_phoneNumber  << "\t" << " 地址：" << m_address  << "\t" << " 价格：" << m_price  << "\t" << "\n";
    }
    PERSON_TYPE getType() const override {
        return personType;
    }
};

// 中介
class ConcreteMediator: public BaseMediator {
private:
    Tenant *tenant;
    Landlord *landlord;
    std::vector<Tenant*> tenantVector;
    std::vector<Landlord*> landlordVector;

public:
    void registerInfo(BaseComponent* component) override {
        if (component->getType() == TENANT) {
            tenantVector.push_back((Tenant*)component);
        } else if (component->getType() == LANDLORD) {
            landlordVector.push_back((Landlord*)component);
        } else {
            std::cerr << "ERROR\n";
        }
    }
    void getInfo(BaseComponent *component) override {
        if(component->getType() == TENANT) {
            for(const auto &landlord : landlordVector) {
                landlord->answer();
            }
            
        } else if (component->getType() == LANDLORD) {
            for(const auto &tenant : tenantVector) {
                tenant->answer();
            }
        }
    }
};


int main(int argc, char * argv[]) {
    ConcreteMediator *mediator = new ConcreteMediator;

    Tenant *t1 = new Tenant("张三", "111111");
    Tenant *t2 = new Tenant("李四", "222222");
    t1->setMediator(mediator);
    t2->setMediator(mediator);
    mediator->registerInfo(t1);
    mediator->registerInfo(t2);

    Landlord *l1 = new Landlord("北京房东", "010-241235", "北京市朝阳区", "5500");
    Landlord *l2 = new Landlord("北京房东", "010-3253523", "北京市大兴区", "3500");
    Landlord *l3 = new Landlord("重庆房东", "023-3463177", "重庆市沙坪坝区", "1500");
    l1->setMediator(mediator);
    l2->setMediator(mediator);
    l3->setMediator(mediator);
    mediator->registerInfo(l1);
    mediator->registerInfo(l2);
    mediator->registerInfo(l3);

    t1->ask();
    std::cout <<"\n";
    l1->ask();

    delete t1;
    delete t2;
    delete l1;
    delete l2;
    delete l3;

    return 0;
}