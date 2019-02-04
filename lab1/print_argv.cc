#include <string>
#include <iostream>
using std::cout;
using std::endl;

/* Example program, printing command line arguments
 * It is good practice to convert the C string
 * i.e., "pointer to first element of a  null-terminated 
 * array of char" to a std::string and then use the
 * safer std::string instead of directly using the C-string.
 */

void print_string(std::string str)
{
    cout << "[" << str << "] ";
}

int main(int argc, char** argv)
{
    cout << "argc=" << argc << endl;

    for(int i=0; i < argc; ++i){
        std::string arg{argv[i]}; // create a std::string for the argument

        print_string(arg);        // pass the std::string to a functio
    }
    cout << endl;
    return 0;
}
