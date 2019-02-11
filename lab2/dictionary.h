#ifndef DICTIONARY_H
#define DICTIONARY_H
#define SIZE 25

#include <string>
#include <vector>
#include <word.h>
#include <unordered_set>

class Dictionary {
public:
	Dictionary();
	bool contains(const std::string& word) const;
	std::vector<std::string> get_suggestions(const std::string& word) const;
private:
	std::unordered_set<std::string> *myDictionary;
	std::vector<Word> words[SIZE];
};

#endif
