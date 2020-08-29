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
