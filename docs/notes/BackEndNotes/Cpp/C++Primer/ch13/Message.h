#ifndef CPPPRIMER_MESSAGE_H
#define CPPPRIMER_MESSAGE_H

#include <string>
#include <set>
#include <utility>
using namespace std;

class Folder;

class Message {
    friend class Folder;
public:
    // folders被隐式初始化为空集合
    explicit Message(string str = ""): contents(std::move(str)) {}

    // 拷贝控制成员，用来管理指向本Message的指针
    Message(const Message&);    // 拷贝构造函数
    Message& operator=(const Message&); // 拷贝赋值运算符
    ~Message(); // 析构函数

    // 从给定Folder集合中添加/删除本Message
    void save(Folder&);
    void remove(Folder&);
    void swap(Message&, Message&);


private:
    string contents;    // 实际消息文本
    set<Folder*> folders;  // 包含本Message的Folder

    void addToFolders(const Message&);  // 将本Message添加到指定参数的Folder中
    void removeFromFolders();   // 从folders中的每个Folder中删除本Message
};

#endif //CPPPRIMER_MESSAGE_H