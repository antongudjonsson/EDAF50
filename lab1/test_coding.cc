#include <iostream>
#include "coding.h"
#include <string>
#include <cassert>

std::string do_encode(std::string s)
{
    for(auto& c : s) {
        c = encode(c);
    }
    return s;
}

std::string do_decode(std::string s)
{
    for(auto& c: s) {
        c = decode(c);
    }
    return s;
}

bool test_coding()
{
    std::string str = "Testing, testing... I should be the same after encoding and decoding";

    std::string enc = do_encode(str);
    assert(enc.size() == str.size()); // sanity check for test program

    bool result = true;
    for(std::string::size_type i=0; i != enc.size(); ++i){
        if(enc[i] == str[i]) {
            std::cout << "enc == str in position " << i << std::endl;
            result = false;
        }
    };

    std::string dec = do_decode(enc);
    assert(enc.size() == dec.size()); // sanity check for test program

    if(str != dec) {
        std::cout << "Expected: " << str << "(" << str.size() <<
                  ")\nActual:   " << dec << "(" << dec.size() << ")" << std::endl;
        result = false;
    }
    return result;
}

int main()
{
    if(test_coding()) {
        std::cout << "Test passed." << std::endl;
    } else {
        std::cout << "Test failed." << std::endl;
    }
    return 0;
}
