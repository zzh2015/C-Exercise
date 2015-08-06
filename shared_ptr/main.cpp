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

    for (auto it=(sb.data)->begin(); it!=(sb.data)->end(); ++it) {
        cout << *it << endl;
    }

    return 0;
}
