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
	ifstream inFile ("words.txt");
	string myWord, aTrigram;
	int nbrTrigrams;
	vector<string>	trigrams;
	
	while(getline(inFile, myWord)){
		
		inFile >> myWord;
		myDictionary->insert(myWord);
		
		inFile >> nbrTrigrams;
		
		for(int i = 0; i < nbrTrigrams; ++i){
			inFile >> aTrigram;
			trigrams.push_back(aTrigram);
		}
		words[myWord.length() - 1].push_back(Word(myWord, trigrams));
		trigrams.clear();
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


