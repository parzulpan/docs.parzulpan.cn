#include "set.h"

template< class T>
bool Set<T>::find(const T& item) const {
    return std::find(rep.begin(), rep.end(), item) != rep.end();
}

template< class T>
void Set<T>::insert(const T& item) {
    if(!find(item)) {
        rep.push_back(item);
    }
}

template< class T>
void Set<T>::remove(const T& item) {
    auto it = std::find(rep.begin(), rep.end(), item);
    if(it != rep.end()) {
        rep.erase(it);
    }
}

template< class T>
std::size_t Set<T>::size() const {
    return rep.size();
}


int main(int argc, char* argv[]) {

    Set<int> s;
    s.insert(10);
    s.insert(5);
    std::cout << s.size() << std::endl;
    std::cout << s.find(5) << std::endl;
    s.remove(5);
    std::cout << s.size() << std::endl;

    return 0;
}