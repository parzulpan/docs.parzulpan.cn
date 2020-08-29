#include <iostream>
#include <string>
#include <vector>
#include "Iterator.h"


int main(int argc, char * argv[]) {
    std::vector<std::string> channels = {"CCTV-1", "CCTV-2", "CCTV-3", "CCTV-4", "CCTV-5", "CCTV-6", "CCTV-7", "CCTV-8"};
    Television *tv = new Television(channels);
    Iterator *remoteControl = tv->createIterator();
    
    for(remoteControl->first(); remoteControl->hasNext(); remoteControl->next()) {
        remoteControl->currentChannel();
    }

    for(remoteControl->last(); remoteControl->hasPrevious(); remoteControl->previous()) {
        remoteControl->currentChannel();
    }

    return 0;
}