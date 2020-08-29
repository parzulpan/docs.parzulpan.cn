#include <iostream>
#include <new>

void outOfMemory() {
    std::cerr << "Unable to statisfy request for memory" << std::endl;
    std::abort();
}

int main(int argc, char* argv[]) {
    std::set_new_handler(outOfMemory);
    // std::set_new_handler(nullptr);
    int* pbigDataArray = new int[1000000000000000000L];
    return 0;
}