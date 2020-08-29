# -*- coding: utf-8 -*-


class Target:

    def request(self):
        return "Target: The default target's behavior."


class Adaptee:

    def specific_request(self):
        return ".eetpadA eht fo roivaheb laicepS"


class Adapter(Target, Adaptee):

    def request(self):
        return "Adapter: (TRANSLATED) {0}".format(self.specific_request()[::-1])


def client_code(target):

    print(target.request())


if __name__ == "__main__":
    print("Client: 处理任何数据")
    target = Target()
    client_code(target)
    print("\n")

    print("Client: 我不能理解这个数据")
    adaptee =  Adaptee()
    print("Adaptee: {0}".format(adaptee.specific_request()))
    print("\n")

    print("Client: 结合适配器可以理解这个数据")
    adapter = Adapter()
    client_code(adapter)