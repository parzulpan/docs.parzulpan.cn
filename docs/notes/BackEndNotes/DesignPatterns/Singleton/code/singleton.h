#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <pthread.h>
#include <unistd.h>

// 单线程版本
class Singleton {
public:
    static Singleton* getInstance() {   // 提供外部接口，满足了第三个要点
        if(instance == nullptr) {
            std::cout << "New Singleton" << std::endl;
            instance = new Singleton();
        }
        return instance;
    }
private:
    Singleton(){}   // 构造函数是私有的，即只能在类内部实例化，满足了第二个要点
    static Singleton* instance; // instance是static的，满足了第一个要点
};

Singleton* Singleton::instance = nullptr;


// 线程安全的多线程版本
class SingletonA {
public:
    static SingletonA* getInstance() {
        if(instance == nullptr) {
            m_mutex.lock(); // 添加互斥锁
            // std::lock_guard<std::mutex> lock(m_mutex);
            if(instance == nullptr) {
                std::cout << "New SingletonA" << std::endl;
                instance = new SingletonA();
            }
            m_mutex.unlock();
        }
        return instance;
    }

private:
    SingletonA() {}
    static SingletonA* instance;
    static std::mutex m_mutex;
};

SingletonA* SingletonA::instance = nullptr;
std::mutex SingletonA::m_mutex;

#endif  //__SINGLETON_H__