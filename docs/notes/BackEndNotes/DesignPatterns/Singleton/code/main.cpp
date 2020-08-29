#include "singleton.h"

void* CallSingleton(void *arg) {
    Singleton::getInstance();
    std::cout << "num: " << arg << std::endl;
    return nullptr;
}

void* CallSingletonA(void *arg) {
    SingletonA::getInstance();
    std::cout << "num: " << arg << std::endl;
    return nullptr;
}

int main(int argc, char *argv[]) {
    CallSingleton(0);
    CallSingleton(0);

    CallSingletonA(0);
    CallSingletonA(0);

    // Windows
    std::thread t1(CallSingleton);
    std::thread t2(CallSingleton);
    t1.join();
    t2.join();

    // Linux
    // pthread_t tid[2];
    // pthread_create(&tid[0], NULL, CallSingleton, NULL);
    // pthread_create(&tid[1], NULL, CallSingleton, NULL);

    return 0;
}