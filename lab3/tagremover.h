#ifndef TAGREMOVER_H
#define TAGREMOVER_H

#include <iostream>
using namespace std;

class TagRemover{
public:
    TagRemover(istream& in);
    TagRemover(string s);
    void prune(string s);
    void translate(string filename);
    void print(ostream& out);

};

#endif