#ifndef TAGREMOVER_H
#define TAGREMOVER_H

#include <iostream>
using namespace std;

class TagRemover{
public:
    TagRemover(istream& in);
    TagRemover(const string s);
    void prune();
    void translate();
    void print(ostream& out);
    
    private:
    string taggedText;
    string myFile;

};

#endif