#include "TextQuery.h"

void runQ(std::ifstream &inFile)
{
    TextQuery tq(inFile);

    while (true) {
        std::cout << "enter word lookfor" << std::endl;

        std::string s;

        if (!(std::cin>>s) || ("q" == s))
            break;

        print(std::cout, tq.query(s));

        std::cout << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::ifstream inFile("test.txt");
    runQ(inFile);

    return 0;
}

