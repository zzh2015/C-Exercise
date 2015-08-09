#include "Connection.h"

#include <iostream>

int main(int argc, char *argv[])
{
    Destination des("http connection");

    f(des);

    std::cout << "leave main" << std::endl;

    return 0;
}
