#include <iostream>
#include "bitset.h"
#include "bitreference.h"

/*
 *         TEST, VERSION 1
 * There are two versions of the test program. The first version uses 
 * only operator[] and BitReferences. When this works, implement
 * the class BitsetIterator and use version 2 in bitsettest2.cc.
 *
*/

using namespace std;

void print(const Bitset& bs) {
	for (size_t i = 0; i != bs.size(); ++i) {
		cout << bs[i];
	}
}

int main() {
	// Define an empty bitset, set every third bit, print
	Bitset bs;
	for (size_t i = 0; i < bs.size(); i += 3) {
		bs[i] = true;
	}
	print(bs);
	cout << endl;
	
	// Find the first five bits that are set, complement them, print
	size_t cleared = 0;
	size_t pos = 0;
	while (pos != bs.size() && cleared != 5) {
		if (bs[pos]) {
			bs[pos] = !bs[pos];
			++cleared;
		}
		++pos;
	}
	print(bs);
	cout << endl;

	// Count the number of set bits, print
	size_t set = 0;
	for (size_t i = 0; i != bs.size(); ++i) {
		if (bs[i]) {
			++set;
		}
	}
	cout << "Number of set bits: " << set << endl;
}
