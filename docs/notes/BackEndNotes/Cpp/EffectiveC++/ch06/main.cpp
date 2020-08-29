#include <iostream>
#include <algorithm>
#include <functional>

int main(int argc, char* argv[]) {

    std::function<std::string(int a, int b)> fun;
    fun = [](int a, int b) -> std::string {std::cout << a + b << std::endl; return "funab";};
    std::cout << fun(2, 3) << std::endl;
    return 0;
}