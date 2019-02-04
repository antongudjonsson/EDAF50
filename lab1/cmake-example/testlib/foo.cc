#include <iostream>

void foo_fun()
{
    auto x = 17; // use a C++11 feature to see if flags are set correctly
    std::cout << "[foo: " << x << "]" << "\n";
}
