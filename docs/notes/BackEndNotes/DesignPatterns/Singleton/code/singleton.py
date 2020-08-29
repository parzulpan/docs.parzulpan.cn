from threading import Thread, Lock


# 单线程版本，使用元类
class SingletonMeta(type):

    _instance = {}

    def __call__(cls, *args, **kw):
        if cls not in cls._instance:
            instance = super().__call__(*args, **kw)
            cls._instance[cls] = instance
        return cls._instance[cls]


class TestSingleton(metaclass=SingletonMeta):
    def some_business_logic(self):
        # ...
        pass


# 线程安全的多线程版本，使用元类
class SingletonMateA(type):

    _instance = {}
    _lock: Lock = Lock()

    def __call__(cls, *args, **kw):
        with cls._lock:
            if cls not in cls._instance:
                instance = super().__call__(*args, **kw)
                cls._instance[cls] = instance
        return cls._instance[cls]


class TestSingletonA(metaclass=SingletonMateA):
    value :str = None

    def __init__(self, value: str) -> None:
        self.value = value

    def some_business_logic(self):
        # ...
        pass


def TestTestSingletonA(value: str) -> None:
    rsa = TestSingletonA(value)
    print(rsa.value)


if __name__ == "__main__":
    # 
    s1 = TestSingleton()
    s2 = TestSingleton()
    if id(s1) == id(s2):
        print(id(s1))
    else:
        print(id(s1), id(s2))

    # 
    process1 = Thread(target=TestTestSingletonA, args=("FOO",))
    process2 = Thread(target=TestTestSingletonA, args=("BAR",))
    process1.start()
    process2.start()