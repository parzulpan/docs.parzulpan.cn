# -*- coding: utf-8 -*-

from abc import ABC, abstractmethod


class Subject(ABC):
    """
    """

    @abstractmethod
    def request(self) -> None:
        pass


class RealSubject(Subject):
    """
    """

    def request(self) -> None:
        print("RealSubject: 处理要求.")


class Proxy(Subject):
    """
    """

    def __init__(self, real_subject: RealSubject) -> None:
        self._real_subject = real_subject

    def request(self) -> None:
        if self.check_access():
            self._real_subject.request()
            self.log_access()

    def check_access(self) -> bool:
        print("Proxy:在发出真实请求之前检查访问权限。")
        return True

    def log_access(self) -> None:
        print("Proxy: 记录请求时间。", end="")


def client_code(subject: Subject) -> None:
    # ...

    subject.request()

    # ...


if __name__ == "__main__":
    print("Client: 执行真实角色:")
    real_subject = RealSubject()
    client_code(real_subject)

    print("")

    print("Client: 执行代理角色:")
    proxy = Proxy(real_subject)
    client_code(proxy)