#include "Employee.h"
#include "TestString.h"

int main(int argc, char *argv[])
{
#if 0
    Employee *em = new Employee();

    std::cin >> *em;

    std::cout << *em << std::endl;
#endif
    std::string str{"Hello World!"};
    TestString *ts = new TestString(str); 
   
    std::cin >> *ts;

    std::cout << *ts << std::endl; 

    std::cout << ts[0] << std::endl;

    return 0;
}

