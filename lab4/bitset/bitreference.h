/*
 * A BitReference is a "pointer to a bit" in a Bitset. It
 * has a reference to the word containing the bits (p_bits)
 * and an int (pos) which is the position of the bit in the word.
 */

#ifndef BITSET_REFERENCE_H
#define BITSET_REFERENCE_H

#include "bitset.h"
#include <cstddef>

class BitReference {
	// friend class BitsetIterator;
public:
	BitReference(Bitset::BitStorage* pb, std::size_t p)
	    : p_bits(pb), pos(p) {}
	
	/*
	 * This operator= is used for bs[i] = b.
	 */
	BitReference& operator=(bool b);
	
	/*
	 * This operator= is used for bs[i] = bs[j].
	 */
	BitReference& operator=(const BitReference& rhs);
	
	/*
	 * Operator bool() is used for b = bs[i].
	 */
	operator bool() const;
private:
	Bitset::BitStorage* p_bits; // pointer to the word containing bits
	std::size_t pos;            // position of the bit in the word
};

#endif
