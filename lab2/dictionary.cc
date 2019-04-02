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
		if(myWord.length() <= 25){
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
}

bool Dictionary::contains(const string& word) const {
	/*for(auto itr = myDictionary->begin(); itr != myDictionary->end(); ++itr){
		if(*itr == word){
			return true;
		}
	}*/
	if(myDictionary->count(word)){
		return true;
	}
	return false;
}

vector<string> Dictionary::get_suggestions(const string& word) const {
	vector<string> suggestions;
	add_trigram_suggestions(suggestions, word);
	rank_suggestions(suggestions, word);
	trim_suggestions(suggestions, word);
	return suggestions;
}

void Dictionary::add_trigram_suggestions(std::vector<std::string>& suggestions, const std::string& myWord) const{
	int nbrTrigrams = myWord.length() - 2;
	vector<string> trigrams;
	if(nbrTrigrams > 0){
		for(int i = 0; (unsigned) i < nbrTrigrams; ++i){
        	trigrams.push_back(myWord.substr(i,3));
    	}
	}
	sort(trigrams.begin(), trigrams.end());
	
	int minLength;
	int maxLength;

	if(myWord.length() == 1){
		minLength = myWord.length() - 1;
		maxLength = myWord.length();
	}else if(myWord.length() == 25){
		minLength = myWord.length() - 2;
		maxLength = myWord.length() - 1;
	}else{
		minLength = myWord.length() - 2;
		maxLength = myWord.length();
	}

	int matches;
	for(int i = minLength; i <= maxLength; i++){
		for(Word w : words[i]){
			matches = w.get_matches(trigrams);
			if(matches >= trigrams.size() / 2){
				suggestions.push_back(w.get_word());
			}
		}
	}
}

void Dictionary::rank_suggestions(std::vector<std::string>& suggestions, const std::string& myWord) const{
	vector<pair<int, string>> score;
	int row = myWord.length();
	for(string possibility : suggestions){
		int d[SIZE+1][SIZE+1];
		d[0][0] = 0;
		int col = possibility.length();
		for(int i = 0; i <= row; ++i){ d[i][0] = i;}
		for(int j = 0; j <= col; ++j){ d[0][j] = j;}

		for(int i = 1; i <= row; ++i){
			for(int k = 1; k <= col; ++k){
				d[i][k] = min({d[i][k-1] + 1, d[i-1][k] + 1, d[i-1][k-1] + (myWord[i-1] == possibility[k-1] ? 0 : 1)});
			}
		}
		score.push_back(make_pair(d[row][col], possibility));
	}
	sort(score.begin(), score.end());
	suggestions.clear();
	for(pair<int,string> p : score){
		suggestions.push_back(p.second);
	}
}

void Dictionary::trim_suggestions(std::vector<std::string>& suggestions, const std::string& myWord) const{
	if(suggestions.size() > 5){
		suggestions.resize(5);
	}
}


