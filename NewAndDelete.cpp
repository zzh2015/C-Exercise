#include <iostream>
#include <memory>
#include <vector>

using namespace std;

static vector<int> *GetVector()
{
    cout << "new vector<int>" << endl;

    return new vector<int>;
}

static vector<int> *AddVector(vector<int> *v, int data)
{
    v->push_back(data);

    return v;
}

static void PrintVector(vector<int> *v)
{
    for (auto it=v->begin(); it!=v->end(); ++it)
        cout << "value = " << *it << endl;
}

static void ReleaseVector(vector<int> *v)
{
    delete v;

    cout << "delete vector<int>" << endl;
}

int main(int argc, char *argv[])
{
    auto v = GetVector();

    for (int i=0; i!=10; ++i)
        AddVector(v, i);

    PrintVector(v);

    ReleaseVector(v);

    return 0;
}
