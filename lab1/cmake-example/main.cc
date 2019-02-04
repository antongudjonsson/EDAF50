#include <iostream>
#include "SimpleConfig.h"
#include "foo.h"



using std::cout;
using std::endl;

int main()
{
    cout << "This is version " << Simple_VERSION_MAJOR << "." <<
        Simple_VERSION_MINOR << "\n";
    cout << "Hello, world!\n";
    foo_fun();
}


