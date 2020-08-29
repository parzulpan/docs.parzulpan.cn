#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <iostream>
#include <vector>
#include <string>
#include "Iterator.h"
using namespace std;

// 前向声明，因为两个类互相引用
class Iterator;
class RemoteControl;

// 抽象聚合类 Aggregate
class Aggregate
{
public:
	Aggregate(){}
	virtual Iterator* createIterator() = 0;
};

// 具体聚合类 Television
class Television :public Aggregate
{
public:
	Television();
	Television(vector<string> iChannelList) : channelList(iChannelList) {}
	// 实现创建迭代器
	Iterator* createIterator() {
        RemoteControl *it = new RemoteControl();
	    it->setTV(this);
	    return (Iterator*)it;
    }
	// 获取总的频道数目
	int getTotalChannelNum() {
        return channelList.size();
    }
	void play(int i) {
        cout << "现在播放：" << channelList[i] << endl;
    }
private:
	vector<string> channelList;
};

#endif