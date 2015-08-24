#include "HasPtr.h"

using namespace std;

int main(int argc, char *argv[])
{
#if VERSION
    
    string str{"Hello World!"};
    HasPtr p1(str);

    HasPtr p2 = p1, p3;
    
    p3 = p1;

    cout << "p1: " <<endl;
    p1.print();

    cout << "p2: " <<endl;
    p2.print();

    cout << "p3: " <<endl;
    p3.print();

#else

    string str{"Hello Copy!!"};
    HasPtr p1(str);

    HasPtr p2 = p1, p3;
    
    p3 = p1;

    cout << "p1: " <<endl;
    p1.print();

    cout << "p2: " <<endl;
    p2.print();

    cout << "p3: " <<endl;
    p3.print();

#endif

    return 0;
}

