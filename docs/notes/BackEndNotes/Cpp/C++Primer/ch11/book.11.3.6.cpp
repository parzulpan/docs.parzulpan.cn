// 给定一个string，将它转换为另一个string。程序的输入是两个文件。第一个文件保存一些规则，用来转换第二个文件中的文本。
// 每条规则由两部分组成：一个可能出现在输入文件中的单词和一个替换它的短语。

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
//#include <algorithm>

using namespace std;

// 转换映射
map<string, string> buildMap(ifstream &map_file) {
    map<string, string> trans_map;
    string key;
    string value;

    while(map_file >> key && getline(map_file, value)) {
        if(value.size() > 1)
            trans_map[key] = value.substr(1);
        else
            throw runtime_error("no rule for " + key);
    }
    return trans_map;
}

// 生成转换文本
const string & transform(const string &s, const map<string, string> &m) {
    auto map_it = m.find(s);
    if(map_it != m.cend())
        return map_it->second;
    else
        return s;
}

// 单词转换
void word_transform(ifstream &map_file, ifstream &input) {
    auto trans_map = buildMap(map_file);
    string text;
    while(getline(input, text)) {
        istringstream stream(text);
        string word;
        bool firstWord = true;
        while(stream >> word) {
            if(firstWord)
                firstWord = false;
            else
                cout << " ";

            cout << transform(word, trans_map);
        }
        cout << endl;
    }
}

int main() {
    ifstream map_file_in("../ch11/map_file.txt");
    ifstream input_in("../ch11/input.txt");

    word_transform(map_file_in, input_in);

    return 0;
}

