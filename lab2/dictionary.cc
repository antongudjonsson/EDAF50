#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <unordered_set>
#include <iterator>
#include "word.h"
#include "dictionary.h"

using std::string;
using std::vector;
using namespace std;

Dictionary::Dictionary() {
	myDictionary = new unordered_set<string>;
	ifstream inFile ("words");
	string myWord;
	while(getline(inFile, myWord)){
		myWord.erase(std::remove_if(myWord.begin(), myWord.end(),  [](char c){ return std::isspace(static_cast<unsigned char>(c));}), myWord.end());
		transform(myWord.begin(), myWord.end(), myWord.begin(), ::tolower);
		myDictionary->insert(myWord);
	}
}

bool Dictionary::contains(const string& word) const {
	for(auto itr = myDictionary->begin(); itr != myDictionary->end(); ++itr){
		if(*itr == word){
			return true;
		}
	}
	return false;
}

vector<string> Dictionary::get_suggestions(const string& word) const {
	vector<string> suggestions;
	return suggestions;
}


