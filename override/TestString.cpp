#include "TestString.h"

TestString::TestString(const std::string &s)
{
    m_Str = new std::string(s);

}

TestString::~TestString()
{
    delete m_Str;
}

TestString::TestString(const TestString &ts)
{
    m_Str = new std::string(*ts.m_Str);
}

TestString &TestString::operator=(const TestString &ts)
{
    if (this == &ts)
        return *this;

    delete m_Str;
    
    m_Str = new std::string(*ts.m_Str);

    return *this;
}

std::ostream &operator<<(std::ostream &os, const TestString &ts)
{
    os << *ts.m_Str;
}

std::istream &operator>>(std::istream &is, TestString &ts)
{
    is >> *ts.m_Str;
}

