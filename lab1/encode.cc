#include <iostream>
#include <string>
#include <fstream>
#include "coding.h"

using std::cout;
using std::endl;
using namespace std;

int main(int argc, char** argv)
{
std::string line;
std::string encoded = "";
std::string filename = argv[1];

ifstream inFile (filename);

if(inFile.is_open()){
    while(getline(inFile, line)){
        for(auto& c : line) {
          encoded += encode(c);
        }
    }
    inFile.close();
}else cout << "Cannot open file." << endl;
cout << encoded;
ofstream outFile;
outFile.open (filename + ".enc");
outFile << encoded;
outFile.close();
}