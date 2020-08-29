#ifndef CPPPRIMER_QUERYRESULT_H
#define CPPPRIMER_QUERYRESULT_H

#include "TextQuery.h"

// 查询结果类
class QueryResult {
friend  ostream& print(ostream&, const QueryResult&);

public:
    QueryResult(string s, shared_ptr<set<TextQuery::line_no>> p, shared_ptr<vector<string>> f): sought(move(s)), lines(move(p)), file(move(f)) {}

private:
    string sought;  // 查询单词
    shared_ptr<set<TextQuery::line_no>> lines; // 出现的行号
    shared_ptr<vector<string>> file; // 输入文件
};


#endif //CPPPRIMER_QUERYRESULT_H
