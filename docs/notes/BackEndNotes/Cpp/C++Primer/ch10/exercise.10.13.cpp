//接受一个string，返回一个bool值，指出string是否有5个或更多字符。并打印出大于等于5的元素。

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

inline void output_words(const vector<string>& words) {
    for(const auto& word: words) {
        cout << word << " ";
    }
    cout << endl;
}

inline void output_words(vector<string>::iterator beg, vector<string>::iterator end) {
    for(auto it = beg; it != end; ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

bool five_or_more(const string &word) {
    return word.size() >= 5;
}


int main(int argc, char* argv[]) {
//    ifstream in (argv[1]);
    ifstream in("../ch10/words.txt");
    if(!in) {
        cout << "打开输入文件失败!" << endl;
        exit(1);
    }

    vector<string> words;
    string word;
    while(in >> word) {
        words.push_back(word);
    }
    output_words(words);
    auto it = partition(words.begin(), words.end(), five_or_more);
    output_words(words.begin(), it);

    return 0;
}

