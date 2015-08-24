#include "HasPtr.h"

#if VERSION

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    auto newp = new std::string(*(rhs.ps));

    delete ps;

    ps = newp;
    i = rhs.i;

    return *this;
}

#else

HasPtr::~HasPtr()
{
    if (--(*use)) {
        delete ps;
        delete use;
    }
}

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    ++(*rhs.use);

    if (0 == --(*use)) {
        delete ps;
        delete use;
    }

    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;

    return *this;
}

#endif

