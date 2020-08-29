# -*- coding: utf-8 -*-

from __future__ import annotations
from abc import ABC, abstractmethod
from typing import Any, Optional

class Handler(ABC):
    """
    """

    @abstractmethod
    def set_next(self, handler: Handler) -> Handler:
        pass

    @abstractmethod
    def handle(self, request) -> Optional[str]:
        pass


class AbstractHandler(Handler):
    """
    """
    _next_handler: Handler = None
    
    def set_next(self, handler: Handler) -> Handler:
        self._next_handler = handler
        return handler

    @abstractmethod
    def handle(self, request: Any) -> str:
        if self._next_handler:
            return self._next_handler.handle(request)
        
        return None


class ConcreteHandlerA(AbstractHandler):
    """
    """
    def handle(self, request: Any) -> str:
        if request == "A":
            return f"A: 我 能 处 理 它 {request}"
        else:
            return super().handle(request)


class ConcreteHandlerB(AbstractHandler):
    """
    """
    def handle(self, request: Any) -> str:
        if request == "B":
            return f"B: 我 能 处 理 它 {request}"
        else:
            return super().handle(request)


class ConcreteHandlerC(AbstractHandler):
    """
    """
    def handle(self, request: Any) -> str:
        if request == "C":
            return f"C: 我 能 处 理 它 {request}"
        else:
            return super().handle(request)


def client_code(handler: Handler) -> None:
    for r in ["B", "A", "D"]:
        print(f"Client: 谁 能 处 理 {r} ?")
        result = handler.handle(r)
        if result:
            print(f" {result}")
        else:
            print(f" {r} 不 能 被 处 理.")


if __name__ == "__main__":
    a = ConcreteHandlerA()
    b = ConcreteHandlerB()
    c = ConcreteHandlerC()
    a.set_next(b).set_next(c)

    print("Chain: A > B > C")
    client_code(a)
    print("\n")

    print("Subchain: B > C")
    client_code(b)
