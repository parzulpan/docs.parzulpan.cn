#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream in("../ch08/example.txt");
    if (!in) {
        cerr << "open file error." << endl;
        return -1;
    }

    string line;
    vector<string> words;
    while (getline(in, line)) {
        words.push_back(line);
    }
    in.close();

    for(const auto& it: words) {
        cout << it << endl;
    }

    return 0;
}
