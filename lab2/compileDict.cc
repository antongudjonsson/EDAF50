#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using std::endl;
using std::cout;
using namespace std;

int main(){
    std::string filename = "words";
    std::string line;
    std::string temp = "";
    int count = 0;

    ifstream inFile (filename);
    ofstream outFile;
    outFile.open(filename + ".txt");

    /*while(!inFile.eof()){
        inFile >> line;
        inFile.ignore();
        if(line.length() > 3){
            for(int i = 0; (unsigned) i < line.length() - 2; ++i){
                temp.append(line.substr(i,3));
                temp.append(" ");
                count++;
            }
        }
        outFile << line + " " + std::to_string(count) + " " + temp << endl;
        temp = "";
        count = 0;
    }*/
    vector<string> trig;
    while(!inFile.eof()){
        inFile >> line;
        inFile.ignore();
        transform(line.begin(), line.end(), line.begin(), ::tolower);

        if(line.length() > 3){
            for(int i = 0; i < line.length() - 2; ++i){
                trig.push_back(line.substr(i,3));
                count++;
            }
            sort(trig.begin(), trig.end());
            for(string s : trig){
                temp.append(s + " ");
            }
        }
        outFile << line + " " + std::to_string(count) + " " + temp << endl;
        temp = "";
        count = 0;
        trig.clear();
    }
    outFile.close();
}