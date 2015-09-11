#include <functional>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int add (int i, int j)
{
    return i+j;
}

auto mod = [](int i, int j) { return i % j; };

struct divide {
    int operator() (int denominator, int divisor) {
        return denominator / divisor;
    }
};

int main(void)
{
    map<string, function<int(int, int)>> binops = {
        {"+", add},
        {"-", minus<int>()},
        {"*", [](int i, int j) {return i*j;}},
        {"/", divide()},
        {"%", mod}
    };

    cout << binops["+"](10, 5) << endl;
    cout << binops["-"](10, 5) << endl;
    cout << binops["*"](10, 5) << endl;
    cout << binops["/"](10, 5) << endl;
    cout << binops["%"](10, 5) << endl;

    return 0;
}

