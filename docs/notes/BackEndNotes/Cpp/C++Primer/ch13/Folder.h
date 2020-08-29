#ifndef CPPPRIMER_FOLDER_H
#define CPPPRIMER_FOLDER_H

#include <string>
#include <set>
#include <utility>
#include <cstring>
using namespace std;

class Message;

class Folder {
    friend class Message;
public:
    explicit Folder (std::string  fld = "") : folderName (std::move(fld)){}
    ~Folder ();

    Folder (const Folder&);

    Folder& operator = (const Folder&);

    void addToMsg (const Folder&);
    void rmFromMsg ();

    //
    void addMsg (Message*);
    void removeMsg (Message*);

    string& getFldName (){ return folderName; }

private:

    string folderName;
    set<Message*> msgs; // 保存文件夹中所有消息的指针

};

#endif //CPPPRIMER_FOLDER_H