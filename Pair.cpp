#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    vector<string> v{"hello", "world", "C++", "python", "git", "c"};

    vector<pair<string, int>> vp;

    for (auto it=v.begin(); it!=v.end(); ++it) {
        vp.push_back(make_pair(*it, (*it).size()));
    }
#if 0
    for (auto it=vp.begin(); it!=vp.end(); ++it) {
        cout << "string: " << (*it).first
            << " int: " << (*it).second << endl;
    }
#endif
    for (auto it : vp) {
        cout << "string: " << it.first
            << " int: " << it.second << endl;
    }

    return 0;
}
