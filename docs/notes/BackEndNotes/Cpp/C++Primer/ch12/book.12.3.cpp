#include "TextQuery.h"
#include "QueryResult.h"

ostream &print(ostream &os, const QueryResult &qr) {

    os << qr.sought << " occurs " << qr.lines->size() << " " << (qr.lines->size() > 1 ? "times": "time") << endl;

    for(auto num: *qr.lines)
        os << "\t( line " << num + 1 << " ) " << *(qr.file->begin() + num) << endl;

    return os;
}

void runQuery(ifstream &file) {
    TextQuery tq(file);
    while (true) {
        cout << "enter word to look for, or q to quit." << endl;
        string s;
        if(!(cin >> s) || s == "q")
            break;
        print(cout, tq.query(s)) << endl;
    }
}

int main() {
    ifstream file("../ch12/query.txt");
    runQuery(file);

    return 0;
}

