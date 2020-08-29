#ifndef CPPPRIMER_TEXTQUERY_H
#define CPPPRIMER_TEXTQUERY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <utility>
using namespace std;


class QueryResult;


// 文本查询程序类
class TextQuery {
public:
    using line_no = vector<string>::size_type;
    explicit TextQuery(ifstream&);
    QueryResult query(const string&) const;

private:
    shared_ptr<vector<string>> file;    // 输入文件
    map<string, shared_ptr<set<line_no>>> wm;   // 每个单词到它所在的行号的集合的映射
};


#endif //CPPPRIMER_TEXTQUERY_H
