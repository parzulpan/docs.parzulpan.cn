#include <iostream>

int main(){

    int i = 5, j = 10;

    int *p = &i;
    std::cout << p << " " << *p << std::endl;   // 0x61fe88 5

    p = &j;
    std::cout << p << " " << *p << std::endl;   // 0x61fe84 10

    *p = 20;
    std::cout << p << " " << *p << std::endl;   // 0x61fe84 20

    j = 30;
    std::cout << p << " " << *p << std::endl;   // 0x61fe84 30

    return 0;
}


