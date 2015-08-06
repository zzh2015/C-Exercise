#include "StrBlob.h"

StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> il) : 
    data(make_shared<vector<string>>(il)) {}

void StrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size()) {
        throw out_of_range(msg);
    }
}

string& StrBlob::front()
{
    check(0, "front on empty StrBolb");

    return data->front();
}

string& StrBlob::back()
{
    check(0, "back on empty StrBolb");

    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBolb");

    data->pop_back();
}

