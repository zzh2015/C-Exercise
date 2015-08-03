#include <iostream>
#include <map>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
    //统计输入的单词出现的次数
    map<string, size_t> word_count;
    //忽略的单词
    set<string> exclude{"the", "but", "and",  "or"};

    string word;

    while ((cin >> word) && (word != "-1")) {
        if (exclude.find(word) == exclude.end()) {
            ++word_count[word];
        }
    }

    //遍历map元素
    for (const auto &w : word_count) {
        cout << w.first << " occurs " << w.second
            << ((w.second>1) ? " times" : " time")
            << endl;
    }

    return 0;
}
