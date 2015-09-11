#ifndef TESTSTRING_H
#define TESTSTRING_H

#include <iostream>
#include <string>

class TestString {
    public:
        TestString(const std::string &s);
        ~TestString(); 

        TestString(const TestString &);
        TestString &operator=(const TestString &);

        friend std::ostream &operator<<(std::ostream &os, const TestString &);
        friend std::istream &operator>>(std::istream &is, TestString &);

        std::string & operator[] (std::size_t n)
        { return m_Str[n]; }
        const std::string & operator[] (std::size_t n) const
        { return m_Str[n]; }

    protected:

    private:
        std::string *m_Str;
};

#endif //TESTSTRING_H

