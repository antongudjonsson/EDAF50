#include "tagremover.h"
#include <iostream>
#include <fstream>

using namespace std;
using std::cout;
using std::endl;

int failed = 0;
int success = 0;

void remove_tags(){
    string filename = "test-original.html";
    string line;
    string key;
    TagRemover tr(filename);
    tr.prune();
    ifstream inFile (filename);
    ifstream keyFile ("key-tags.html");
    if(inFile.is_open()){
        while(!inFile.eof() && !keyFile.eof()){
            getline(inFile, line);
            getline(keyFile, key);
            if(key.compare(line) != 0){
                cout << "remove_tags: Failed on line:" << endl;
                cout << line << " == " << key << endl;
                ++failed;
                inFile.close();
            }
        }
    ++success;
    }
}   

void translate_special(){
    string filename = "test-original.html";
    string line;
    string key;
    TagRemover tr(filename);
    tr.translate();
    ifstream inFile (filename);
    ifstream keyFile ("key-trans.html");
    if(inFile.is_open()){
        while(!inFile.eof() && !keyFile.eof()){
            getline(inFile, line);
            getline(keyFile, key);
            if(key.compare(line) != 0){
                cout << "translate_special: Failed on line:" << endl;
                cout << line << " == " << key << endl;
                ++failed;
                inFile.close();
            }
        }
    ++success;
    }
}

int main() {
    remove_tags();
    translate_special();
    cout << "Success: " << success << endl;
    cout << "Failed: " << failed << endl;
}

