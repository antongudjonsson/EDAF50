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
    int x = 7 / 2;
    cout << std::to_string(x) << endl;

    ifstream inFile (filename);
    ofstream outFile;
    outFile.open(filename + ".txt");

    vector<string> trig;
    while(!inFile.eof()){
        inFile >> line;
        inFile.ignore();
        transform(line.begin(), line.end(), line.begin(), ::tolower);

        if(line.length() > 3){
            for(int i = 0; (unsigned) i < line.length() - 2; ++i){
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