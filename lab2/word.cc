#include <string>
#include <vector>
#include "word.h"

using std::vector;
using std::string;

Word::Word(const string& w, const vector<string>& t) {
	word = w;
	trigrams = t;
}

string Word::get_word() const {
	return word;
}

unsigned int Word::get_matches(const vector<string>& t) const {
	int count = 0;
	for(string myTrigram : t){
		for(string wordTrigram : trigrams){
			if(myTrigram.compare(wordTrigram) == 0){
				count++;
			}else if(myTrigram.compare(wordTrigram) < 0){
				break;
			}
		}
	}
	return count;
}
