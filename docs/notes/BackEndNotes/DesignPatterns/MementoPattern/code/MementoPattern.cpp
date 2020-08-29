#include <iostream>
#include <string>
#include <vector>
#include <ctime>

// 抽象备忘录
class Memento {
public:
    virtual ~Memento() {}
    virtual std::string getName() const = 0;
    virtual std::string date() const = 0;
    virtual std::string state() const = 0;
};

// 具体备忘录
class ConcreteMemento: public Memento {
private:
    std::string m_state;
    std::string m_date;

public:
    ConcreteMemento(std::string state) {
        m_state = state;
        std::time_t now = std::time(0);
        m_date = std::ctime(&now);
    }
    std::string getName() const override {
        return m_date + " / (" + m_state.substr(0, 9) + "...)";
    }
    std::string date() const override {
        return m_date;
    }
    std::string state() const override {
        return m_state;
    }
};

// 原发器
class Originator {
private:
    std::string m_state;
    std::string generateRandomString(int length = 10) {
        const std::string alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int alphanumLength = alphanum.size() - 1;
        std::string randomString;
        for(int i = 0; i < length; i++) {
            randomString += alphanum[std::rand() % alphanumLength];
        }
        return randomString;
    }

public:
    Originator(std::string state) : m_state(state) {
        std::cout << "原发器：初始化状态为 " << m_state << std::endl;
    }
    void doSomeBusinessLogic() {
        std::cout << "原发器：执行一些操作。\n";
        m_state = this->generateRandomString(30);
        std::cout << "原发器：状态变成为 " << m_state << std::endl;
    }
    Memento *save() {
        return new ConcreteMemento(m_state);
    }
    void restore(Memento *memento) {
        m_state = memento->state();
        std::cout << "原发器：状态变成为 " << m_state << std::endl;
    }
};

// 负责人
class Caretaker {
private:
    std::vector<Memento *> m_mementos;
    Originator *m_originator;

public:
    Caretaker(Originator *originator) : m_originator(originator) {}
    void backup() {
        std::cout << "负责人：保存了原发器状态...\n";
        m_mementos.push_back(m_originator->save());
    }
    void undo() {
        if(!m_mementos.size()) {
            return;
        }
        Memento *memento = m_mementos.back();
        m_mementos.pop_back();
        std::cout << "负责人：恢复状态到 " << memento->getName() << "\n";
        try {
            m_originator->restore(memento);
        } catch (...) {
            this->undo();
        }
    }
    void showHistory() const {
        std::cout << "负责人：历史操作记录：\n";
        for(Memento *memento : m_mementos) {
            std::cout << memento->getName() << "\n";
        }
    }

};

void ClientCode() {
    Originator *originator = new Originator("Super-super-super.");
    Caretaker * caretaker = new Caretaker(originator);
    caretaker->backup();
    originator->doSomeBusinessLogic();
    std::cout << "\n";
    caretaker->backup();
    originator->doSomeBusinessLogic();
    std::cout << "\n";
    caretaker->backup();
    originator->doSomeBusinessLogic();
    std::cout << "\n";

    caretaker->showHistory();
    std::cout << "\n";

    std::cout << "Client：回滚一次！\n";
    caretaker->undo();
    std::cout << "\n";
    std::cout << "Client：再回滚一次！\n";
    caretaker->undo();

    delete originator;
    delete caretaker;
}

int main(int argc, char *argv[]) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    ClientCode();

    return 0;
}