#include <iostream>
#include <string>
#include <list>


// 抽象订阅者
class BaseSubscriber {
public:
    virtual ~BaseSubscriber() {}
    virtual void update(const std::string &msgFromPublisher) = 0;
};

// 抽象发布者
class BasePublisher {
public:
    virtual ~BasePublisher() {}
    virtual void attach(BaseSubscriber *subscriber) = 0;
    virtual void detach(BaseSubscriber *subscriber) = 0;
    virtual void notify() = 0;
};

// 具体发布者
class Publisher : public BasePublisher {
private:
    std::list<BaseSubscriber*> m_subscribers;
    std::string m_msg;

public:
    virtual ~Publisher() {
        std::cout << "发布者离开\n";
    }
    void attach(BaseSubscriber *subscriber) override {
        m_subscribers.push_back(subscriber);
    }
    void detach(BaseSubscriber *subscriber) override {
        m_subscribers.remove(subscriber);
    }
    void notify() override {
        std::list<BaseSubscriber*>::iterator it = m_subscribers.begin();
        getSubscriberCnt();
        while (it != m_subscribers.end())
        {
            (*it)->update(m_msg);
            ++it;
        }
    }
    void createMsg(std::string msg = "NULL") {
        std::cout << "发布者发布消息 ---> " << msg << "\n";
        this->m_msg = msg;
        notify();
    }
    void getSubscriberCnt() {
        std::cout << "当前订阅者个数为：" << m_subscribers.size() << "\n";
    }
    void doSomeBusinessLogic() {
        m_msg = "change msg";
        notify();
        std::cout << "需要做一些重要的事" <<"\n";
    }
};

// 具体订阅者
class Subscriber: public BaseSubscriber {
private:
    std::string m_msgFromPublisher;
    Publisher &m_publisher;
    static int m_staticNumber;
    int m_number;

public:
    Subscriber(Publisher &publisher) : m_publisher(publisher) {
        m_publisher.attach(this);
        std::cout << "我是订阅者\"" << ++Subscriber::m_staticNumber << "\"\n";
        m_number = Subscriber::m_staticNumber;
    }
    virtual ~Subscriber() {
        std:: cout << "订阅者\"" << m_number <<"\"离开\n";
    }
    void update(const std::string &msgFromPublisher) override {
        m_msgFromPublisher = msgFromPublisher;
        printInfo();
    }
    void printInfo() {
        std::cout << "订阅者\"" << m_number << "\":  接收到新消息 ---> " << m_msgFromPublisher << "\n";
    }
    void removeMeFromList() {
        m_publisher.detach(this);
        std::cout << "订阅者\"" << m_number <<"\"从列表中移除\n";
    }
};

int Subscriber::m_staticNumber = 0;

void ClientCode() {
    Publisher *publisher = new Publisher;
    Subscriber *subscribe1 = new Subscriber(*publisher);
    Subscriber *subscribe2 = new Subscriber(*publisher);
    Subscriber *subscribe3 = new Subscriber(*publisher);
    Subscriber *subscribe4;
    Subscriber *subscribe5;
    std::cout << "\n";

    publisher->createMsg("Hello World!");
    std::cout << "\n";

    subscribe3->removeMeFromList();
    std::cout << "\n";

    publisher->createMsg("今天天气怎么样？");
    std::cout << "\n";

    subscribe4 = new Subscriber(*publisher);
    std::cout << "\n";

    subscribe2->removeMeFromList();
    std::cout << "\n";

    subscribe5 = new Subscriber(*publisher);
    std::cout << "\n";

    publisher->createMsg("通知：下午放假！");
    std::cout << "\n";

    subscribe5->removeMeFromList();
    std::cout << "\n";

    subscribe4->removeMeFromList();
    subscribe1->removeMeFromList();
    std::cout << "\n";

    delete subscribe5;
    delete subscribe4;
    delete subscribe3;
    delete subscribe2;
    delete subscribe1;
    delete publisher;
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    ClientCode();
    return 0;
}