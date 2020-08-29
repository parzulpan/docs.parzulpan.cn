#include "Message.h"

void Message::save(Folder &f) {
    folders.insert(&f); // 将给定的Folder添加到我们的Folder列表中
    f.addMsg(this); // 将本Message添加到f的Message集合中
}

void Message::remove(Folder &f) {
    folders.erase(&f);  // 将给定Folder从我们的Folder列表中删除
    f.removeMsg(this); // 将本Message从f的Message集合中删除
}

void Message::swap(Message &lhs, Message &rhs) {
    using std::swap;
    for(auto f: lhs.folders)
        f->removeMsg(&lhs); //

    for(auto f: rhs.folders)
        f->removeMsg(&rhs); //

    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);

    for(auto f: lhs.folders)
        f->addMsg(&lhs); //

    for(auto f: rhs.folders)
        f->addMsg(&rhs); //
}

void Message::addToFolders(const Message &m) {
    for (auto f: m.folders)
        f->addMsg(this); // 对每个包含m的Folder，向该Folder添加一个指向本Message的指针
}

void Message::removeFromFolders() {
    for(auto f: folders)
        f->removeMsg(this); // 对folders中的每个指针，从该Folder中删除本Message

}

Message::Message(const Message &m): contents(m.contents), folders(m.folders) {
    addToFolders(m);    // 将本消息添加到指向m的Folder中
}

Message &Message::operator=(const Message &rhs) {
    // 通过先删除指针再插入它们来处理自赋值情况
    removeFromFolders();    // 更新已有Folder
    contents = rhs.contents;    // 从rhs拷贝消息内容
    folders = rhs.folders;  // 从rhs拷贝Folder指针
    addToFolders(rhs);  // 将本Message添加到那些Folder中
    return *this;
}

Message::~Message() {
    removeFromFolders();
}

