#include <iostream>
#include <memory>
#include <algorithm>

void CallDelete(int* ptr) {
    std::cout << ptr << " 对象被删除" << std::endl;
}

int main(int argc, char* argv[]) {

    std::shared_ptr<int> p = std::make_shared<int>(42);

    std::cout << p << std::endl;

    std::cout << *p << std::endl;

    p = nullptr;    // p内存已被释放

    // 指定删除器
    std::shared_ptr<int> p1(new int(10), CallDelete);
    std::cout << p1 << std::endl;

    return 0;
}

