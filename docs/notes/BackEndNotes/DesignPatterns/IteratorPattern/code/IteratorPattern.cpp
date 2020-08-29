#include <iostream>
#include <string>
#include <vector>

template <typename T, typename U>
class Iterator {
public:
    typedef typename std::vector<T>::iterator iter_type;
    Iterator(U *p_data, bool reverse = false) : m_p_data_(p_data), m_it_(m_p_data_->m_data_.begin()) {}
    void first() {
        m_it_ = m_p_data_->m_data_.begin();
    }
    void next() {
        m_it_++;
    }
    bool isDone() {
        return (m_it_ == m_p_data_->m_data_.end());
    }
    iter_type Current() {
        return m_it_;
    }

private:
    U *m_p_data_;
    iter_type m_it_;
};

template <class T>
class Container {
    friend class Iterator<T, Container>;

private:
    std::vector<T> m_data_;

public:
    void add(T a) {
        m_data_.push_back(a);
    }
    Iterator<T, Container> *CreateIterator() {
        return new Iterator<T, Container>(this);
    }
};

class CustomData {
private:
    int m_data_;

public:
    CustomData(int a = 0) : m_data_(a) {}
    void setData(int a) {
        m_data_ = a;
    }
    int data() const { 
        return m_data_;
    }
};

void ClientCode() {
    std::cout << "Iterator with int:\n";
    Container<int> cont;
    for(int i = 0; i < 10; ++i) {
        cont.add(i);
    }

    Iterator<int, Container<int>> *it = cont.CreateIterator();
    for(it->first(); !it->isDone(); it->next()) {
        std::cout << *it->Current() << std::endl;
    }

    std::cout << "\n";

    std::cout << "Iterator with custom Class:\n";
    Container<CustomData> cont2;
    CustomData a(100), b(1000), c(10000);
    cont2.add(a);
    cont2.add(b);
    cont2.add(c);
    Iterator<CustomData, Container<CustomData>> *it2 = cont2.CreateIterator();
    for(it2->first(); !it2->isDone(); it2->next()) {
        std::cout << it2->Current()->data() << std::endl;
    }

    delete it;
    delete it2;
}

int main(int argc, char *argv[]) {
    ClientCode();

    return 0;
}