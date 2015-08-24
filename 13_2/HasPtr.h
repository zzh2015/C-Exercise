#ifndef __HAS_PTR_H__
#define __HAS_PTR_H__

#include <iostream>
#include <string>

#define VERSION 0

#if VERSION

class HasPtr {
    public:
        HasPtr(const std::string &s = std::string()) :
            ps(new std::string(s)), i(0) {}

        HasPtr(const HasPtr &p) : 
            ps(new std::string(*(p.ps))), i(p.i) {}

        HasPtr& operator=(const HasPtr &);

        ~HasPtr() {delete ps;}

        void print() {std::cout << "ps:"  << *ps <<
            " i:" << i << std::endl;}

    protected:

    private:
        std::string *ps;
        int i;

};

#else

class HasPtr {
    public:
        HasPtr(const std::string &s = std::string()) :
            ps(new std::string(s)), i(0), use(new std::size_t(1)) {}

        HasPtr(const HasPtr &p) : 
            ps(new std::string(*(p.ps))), i(p.i), use(p.use) { ++(*use); }

        HasPtr& operator=(const HasPtr &);

        ~HasPtr();

        void print() { std::cout << "ps:" << *ps << " i:" << i  << 
            " use:" << *use << std::endl; }

    protected:

    private:
        std::string *ps;
        int i;
        std::size_t *use;
};

#endif

#endif

