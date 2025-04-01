#include <iostream>

#include "MyClass.h"

int main(int argc, char* argv[])
{
    MyClass myClass;
    std::cout << myClass.getVersion();

    return 0;
}