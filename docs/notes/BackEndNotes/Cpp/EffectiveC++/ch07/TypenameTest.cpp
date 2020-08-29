#include <iostream>
#include <vector>


template<typename C>
void printTwoValue(const C& container) {    // 打印容器内的第二个元素
    if(container.size() >= 2) {
        // C::const_iterator iter(container.begin());  // Error
        // typename C::const_iterator iter(container.begin()); // Success
        auto iter(container.begin());   // Success
        ++iter;
        int value = *iter;
        std::cout << value << std::endl;
    }
}


int main(int argc, char* argv[]) {

    std::vector<int> vec{1, 2, 3, 4};

    printTwoValue(vec);

    return 0;
}