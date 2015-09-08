#include "Employee.h"

int main(int argc, char *argv[])
{
    Employee *em = new Employee();

    std::cin >> *em;

    std::cout << *em << std::endl;
    

    return 0;
}

