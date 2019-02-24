/*
 * A Bitset is an "array of bits", stored in a word (unsigned long).
 * The word contains BPW ("bits per word") bits.
 *
 */

#ifndef BITSET_H
#define BITSET_H

#include <cstddef> /* size_t */
#include <limits>  /* numeric_limits */

class BitReference;
// class BitsetIterator;

class Bitset {
	friend class BitReference;
	// friend class BitsetIterator;
public:
	Bitset();
	std::size_t size() const;
	bool operator[](std::size_t pos) const;
	BitReference operator[](std::size_t pos);
	
	/*
	using iterator = BitsetIterator;
	iterator begin();
	iterator end();
	 */
private:
	using BitStorage = unsigned long;
	BitStorage bits;
	static const std::size_t
	    BPW = std::numeric_limits<BitStorage>::digits;
};

#endif
