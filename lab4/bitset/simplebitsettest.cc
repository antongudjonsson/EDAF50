#include <iostream>
#include "simplebitset.h"

using namespace std;

void print(const SimpleBitset& bs) {
	for (size_t i = 0; i != bs.size(); ++i) {
		cout << bs.get(i);
	}
}

int main() {
	// Define an empty bitset, set every third bit, print
	SimpleBitset bs;
	for (size_t i = 0; i < bs.size(); i += 3) {
		bs.set(i, true);
	}
	print(bs);
	cout << endl;
	
	// Find the first five bits that are set, complement them, print
	size_t cleared = 0;
	size_t pos = 0;
	while (pos != bs.size() && cleared != 5) {
		if (bs.get(pos)) {
			bs.set(pos, !bs.get(pos));
			++cleared;
		}
		++pos;
	}
	print(bs);
	cout << endl;
	
	// Count the number of set bits, print
	size_t set = 0;
	for (size_t i = 0; i != bs.size(); ++i) {
		if (bs.get(i)) {
			++set;
		}
	}
	cout << "Number of set bits: " << set << endl;
}
