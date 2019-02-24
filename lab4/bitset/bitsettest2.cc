#include <iostream>
#include <algorithm>
#include <iterator>
#include "bitset.h"
#include "bitreference.h"
#include "bitsetiterator.h"

/*
 *		 TEST, VERSION 2
 * This version of the test program uses iterators.
 *
 */

using namespace std;

int main() {
	// Define an empty bitset, set every third bit, print
	Bitset bs;
	for (size_t i = 0; i < bs.size(); i += 3) {
		bs[i] = true;
	}
	copy(bs.begin(), bs.end(), ostream_iterator<bool>(cout));
	cout << endl;
	
	// Find the first five bits that are set, complement them, print
	size_t cleared = 0;
	auto it = bs.begin();
	while (it != bs.end() && cleared != 5) {
		it = find(it, bs.end(), true);
		if (it != bs.end()) {
			*it = !*it;
			++cleared;
			++it;
		}
	}
	copy(bs.begin(), bs.end(), ostream_iterator<bool>(cout));
	cout << endl;
	
	// Count the number of set bits, print
	cout << "Number of set bits: " << count(bs.begin(), bs.end(), true) << endl;
}

