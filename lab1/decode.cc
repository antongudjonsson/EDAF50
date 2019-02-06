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
std::string decoded = "";
std::string filename = argv[1];

ifstream inFile (filename + ".enc");

if(inFile.is_open()){
    while(getline(inFile, line)){
        for(auto& c : line) {
          decoded += decode(c);
        }
    }
    inFile.close();
}else cout << "Cannot open file." << endl;
cout << decoded;
ofstream outFile;
outFile.open (filename + ".dec");
outFile << decoded;
outFile.close();
}