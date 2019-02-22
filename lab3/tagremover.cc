#include <iostream>
#include <fstream>
#include "TagRemover.h"
#include <regex>

using namespace std;
using std::cout;
using std::endl;
using std::string;

TagRemover::TagRemover(istream& in){
    string line;
    while(getline(in,line)){
        taggedText += line + "\n";
    }
}

TagRemover::TagRemover(const string filename){
    myFile = filename;
    ifstream inFile (myFile);
    string line;
    if(inFile.is_open()){
        while(getline(inFile, line)){
            taggedText += line + "\n";
        }
    }
}

void TagRemover::prune(){
    int ltag;
    int rtag;
    int tagSize;
    while(true){
        ltag = taggedText.find_first_of("<");
        rtag = taggedText.find_first_of(">");
        if(ltag == -1){
            break;
        }
        tagSize = rtag - ltag + 1;
        taggedText.erase(ltag, tagSize);
    }
    ofstream outFile;
    outFile.open(myFile);
    outFile << taggedText;
}

void TagRemover::translate(){
    string translated;
    translated = regex_replace(taggedText, std::regex("(&lt;)"), "<");
    translated = regex_replace(translated, std::regex("(&gt;)"), ">");
    translated = regex_replace(translated, std::regex("(&nbsp;)"), " ");
    translated = regex_replace(translated, std::regex("(&amp;)"), "&"); 
    ofstream outFile;
    outFile.open(myFile);
    outFile << translated;
}

void TagRemover::print(ostream& out){

}

/*
int main(){
    TagRemover tr(cin);
}
*/