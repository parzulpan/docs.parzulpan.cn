# 观察者模式

## 简介

![logo](resources/logo.png)

软件系统中的对象并不是孤立存在的，一个对象行为的改变可能会引起其他关联的对象的状态或行为也发生改变。观察者模式建立了一种一对多的联动，一个对象改变时将自动通知其他对象，其他对象将作出反映。

观察者模式中，发生改变的对象称为"**观察目标**"，被通知的对象称为"**观察者**"。**一个观察目标可可以有多个观察者**。

观察者模式又称为**发布-订阅模式**(`Publish-Subscibe`)、**模型-视图模式**(`Model-View`)、**源-监听器模式**(`Source-Listener`)、**从属者模式**(`Dependents`)。

> **观察者模式：定义对象之间的一种一对多的依赖关系，使得每当一个对象状态发生改变时，其相关依赖对象都得到通知并被自动更新。**

## 结构

![uml](resources/uml.png)

## 实现

实现方式：

* 仔细检查业务逻辑，试着将其拆分为两个部分：独立于其他代码的核心功能将作为发布者；其他代码则将转化为一组订阅类。
* 声明订阅者接口。该接口至少应声明一个`update`方法。
* 声明发布者接口并定义一些接口来在列表中添加和删除订阅对象。记住发布者必须仅通过订阅者与它们进行交互。
* 确定存放实际订阅列表的位置并实现订阅方法。通常所有类型的发布者代码看上去都一样，因此将列表放置在直接拓展自发布者接口的抽象类是显而易见的。具体发布者会扩展该类从而继承所有的订阅行为。
* 创建具体发布者类。每次发布者发生了重要事件时都必须通知所有的订阅者。
* 在具体订阅者类中实现通知更新的方法。绝大部分订阅者需要一些与事件相关的上下文数据，这些数据可作为通知方法的参数来传递。
* 客户端必须生成所需的全部订阅者，并在相应的发布者处完成注册工作。

```c++
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
```

```python
# -*- coding: utf-8 -*-

from __future__ import annotations
from abc import ABC, abstractmethod
from random import randrange
from typing import List


class Publisher(ABC):
    """
    抽象发布者
    """
    @abstractmethod
    def attach(self, subscriber: Subscriber) -> None:
        pass

    @abstractmethod
    def detach(self, subscriber: Subscriber) -> None:
        pass

    @abstractmethod
    def notify(self) -> None:
        pass


class ConcretePublisher(Publisher):
    """
    具体发布者
    """
    _state: int = None
    _subscribers: List[Subscriber] = []

    def attach(self, subscriber: Subscriber) -> None:
        print(f"发布者：添加了订阅者{subscriber._name}")
        self._subscribers.append(subscriber)

    def detach(self, subscriber: Subscriber) -> None:
        print(f"发布者：移除了订阅者{subscriber._name}")
        self._subscribers.remove(subscriber)

    def notify(self) -> None:
        print("发布者：发布了消息")
        for subscriber in self._subscribers:
            subscriber.update(self)

    def do_some_business_logic(self) -> None:
        print("发布者：执行一些事情")
        self._state = randrange(0, 10)
        print(f"发布者：目前我的状态为{self._state}")
        self.notify()


class Subscriber(ABC):
    """
    """
    @abstractmethod
    def update(self, publisher: Publisher) -> None:
        pass


class ConcreteSubscriberA(Subscriber):
    """
    """
    _name = "A"

    def update(self, publisher: Publisher) -> None:
        if publisher._state < 3:
            print("订阅者A：通过过滤规则后，接收到消息")


class ConcreteSubscriberB(Subscriber):
    """
    """
    _name = "B"

    def update(self, publisher: Publisher) -> None:
        if publisher._state >= 2 or publisher._state == 0:
            print("订阅者B：通过过滤规则后，接收到消息")


if __name__ == "__main__":

    publisher = ConcretePublisher()

    subscriberA = ConcreteSubscriberA()
    publisher.attach(subscriberA)

    subscriberB = ConcreteSubscriberB()
    publisher.attach(subscriberB)

    publisher.do_some_business_logic()
    publisher.do_some_business_logic()
    publisher.do_some_business_logic()

    publisher.detach(subscriberA)

    publisher.do_some_business_logic()
    publisher.do_some_business_logic()

```

## 实例

### 问题描述

模拟手游和平精英的"我这里有物资"和"救救我"等消息通知。

### 问题解答

```c++
// Example.cpp

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

// 具体订阅者：玩家
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
```

## 总结

观察者模式是一种使用频率非常高的设计模式，几乎无处不在。凡是涉及一对一、一对多的对象交互场景，都可以使用观察者会模式。比如购物车，浏览商品时，往购物车里添加一件商品，会引起UI多方面的变化（购物车里商品数量、对应商铺的显示、价格的显示等）；各种编程语言的GUI事件处理的实现；所有的浏览器事件（mouseover，keypress等）都是使用观察者模式的例子。

### 优点

* 观察者模式实现了稳定的消息更新和传递的机制，通过引入抽象层可以扩展不同的具体观察者角色。
* **支持广播通信**。所有已注册的观察者（添加到目标列表中的对象）都会得到消息更新的通知，简化了一对多设计的难度。
* **符合开闭原则**。增加新的观察者无需修改已有代码，在具体观察者与观察目标之间不存在关联关系的情况下增加新的观察目标也很方便。

### 缺点

* 代码中观察者和观察目标相互引用，存在循环依赖，观察目标会触发二者循环调用，有引起系统崩溃的风险。
* 如果一个观察目标对象有很多直接和间接观察者，将所有的观察者都通知到会耗费大量时间。
* 订阅者的通知顺序是随机的。除非特别控制。

### 场景

* 当一个对象状态的改变需要改变其他对象，或实际对象是事先未知的或动态变化的时，可使用观察者模式。
* 当应用中的一些对象必须观察其他对象时，可使用观察者模式。但仅能在有限时间内或特定情况下使用。

### 与其他模式的关系

* **责任链模式**、**命令模式**、**中介者模式**和**观察者模式**用于处理请求发送者和接收者之间的不同连接方式：
  * 责任链按照顺序将请求动态传递给一系列的潜在接收者，直至其中一名接收者对请求进行处理。
  * 命令在发送者和请求者之间建立单向连接。
  * 中介者清除了发送者和请求者之间的直接连接，强制它们通过一个中介对象进行间接沟通。
  * 观察者允许接收者动态地订阅或取消接收请求。
* **中介者模式**和**观察者模式**之间往往很难区分。在大部分情况下，可以使用其中一种模式，而有时可以同时使用。
  * **中介者**的主要目标是消除一系列系统组件之间的相互依赖。这些组件将依赖于同一个中介者对象。**观察者**的目标是在对象之间建立动态的单向连接，使得部分对象可作为其他对象的附属发挥作用。
  * 有一种流行的中介者模式实现方式依赖于观察者。中介者对象担当发布者的角色，其他组件则作为订阅者，可以订阅中介者的事件或取消订阅。当中介者以这种方式实现时，它可能看上去与观察者非常相似。
  * 假设有一个程序，其所有的组件都变成了发布者，它们之间可以相互建立动态连接。这样程序中就没有中心化的中介者对象，而只有一些分布式的观察者。
