#include <iostream>
#include <string>
#include <list>
#include <algorithm>


enum INFO_TYPE {
    NONE,
    RESOURCE,
    HELP
};

class BasePublisher;

// 抽象订阅者
class BaseSubscriber {
private:
    std::string m_name;

public:
    virtual ~BaseSubscriber() {}
    virtual void call(INFO_TYPE type, BasePublisher *publisher) = 0;
    void setName(const std::string &name) {
        m_name = name;
    }
    std::string getName(){ 
        return m_name;
    }
    void come() {
        std::cout <<"玩家 " << m_name << ": 收到，我来取物资！\n";
    }
    void help() {
        std::cout <<"玩家 " << m_name << ": 坚持住，我来救你！\n";
    }
};

// 抽象发布者
class BasePublisher {
public:
    virtual ~BasePublisher() {}
    virtual void join(BaseSubscriber *subscriber) = 0;
    virtual void leave(BaseSubscriber *subscriber) = 0;
    virtual void notify(INFO_TYPE type, const std::string name) = 0;
};

// 具体发布者：战队中心
class PlayerCenter : public BasePublisher {
private:
    std::list<BaseSubscriber*> m_subscribers;

public:
    void join(BaseSubscriber *subscriber) override {
        if (m_subscribers.size() < 4) {
            std::cout << "玩家 " << subscriber->getName() << ": 加入战队！\n";
            m_subscribers.push_back(subscriber);
        } else {
            std::cout << "战队玩家已满，无法加入！\n";
            return;
        }
        if(m_subscribers.size() == 4) {
            std::cout << "组队成功，不要怂，一起上！\n";
        }
    }
    void leave(BaseSubscriber *subscriber) override {
        if (std::find(m_subscribers.begin(), m_subscribers.end(), subscriber) != m_subscribers.end()) {
            std::cout << "玩家 " << subscriber->getName() << ": 离开战队！\n";
            m_subscribers.remove(subscriber);
        } else {
            std::cout << "玩家 " << subscriber->getName() << ": 不在战队！\n";
        }
    }
    void notify(INFO_TYPE type, const std::string name) override {
        if(type == RESOURCE) {
            for(const auto &subscriber : m_subscribers) {
                if (subscriber->getName() != name) {
                    subscriber->come();
                }
            }

        } else if(type == HELP) {
            for(const auto &subscriber : m_subscribers) {
                if (subscriber->getName() != name) {
                    subscriber->help();
                }
            }
        } else {
            ;
        }
    }
};

class Player: public BaseSubscriber {
public:
    Player(std::string name) {
        setName(name);
    }
    void call(INFO_TYPE type, BasePublisher *publisher) override {
        if(type == RESOURCE) {
           std::cout <<"玩家 " << getName() << ": 我这里有物资！\n";
        } else if (type == HELP) {
            std::cout <<"玩家 " << getName() << ": 救救我！\n";
        } else {
            ;
        }
        publisher->notify(type, getName());
    }
};


int main(int argc, char * argv[]) {
    PlayerCenter *playerCenter = new PlayerCenter();

    Player *A = new Player("A");
    Player *B = new Player("B");
    Player *C = new Player("C");
    Player *D = new Player("D");
    playerCenter->join(A);
    playerCenter->join(B);
    playerCenter->join(C);
    playerCenter->join(D);
    // playerCenter->join(D);
    std::cout << "\n";

    B->call(RESOURCE, playerCenter);
    std::cout << "\n";

    A->call(HELP, playerCenter);
    std::cout << "\n";

    playerCenter->leave(A);
    playerCenter->leave(B);
    playerCenter->leave(C);
    playerCenter->leave(D);
    std::cout << "\n";

    delete playerCenter;
    delete A;
    delete B;
    delete C;
    delete D;

    return 0;
}