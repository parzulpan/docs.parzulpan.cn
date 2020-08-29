#ifndef __SET_H__
#define __SET_H__

#include <iostream>
#include <algorithm>
#include <list>

template <class T>
class Set {
private:
    std::list<T> rep;   // 用来表述Set的数据

public:
    bool find(const T& item) const;
    void insert(const T& item);
    void remove(const T& item);
    std::size_t size() const;
};

#endif