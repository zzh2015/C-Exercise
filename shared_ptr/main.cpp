#include <iostream>

#include "StrBlob.h"


int main(int argc, char *argv[])
{
    StrBlob sb;

    {
        StrBlob sb2 = {"acer", "lenove"};

        sb = sb2;

        sb2.push_back("HP");
        sb2.push_back("apple");
    }

    std::cout << sb.front() << std::endl;
    for (auto it=sb.begin(); it!=sb.end(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << sb.back() << std::endl;

    return 0;
}
