/*
 * A SimpleBitset is an "array of bits", stored in a word (unsigned
 * long). The word contains BPW ("bits per word") bits.
*/

#ifndef SIMPLE_BITSET_H
#define SIMPLE_BITSET_H

#include <cstddef> /* size_t */
#include <limits>  /* numeric_limits */

class SimpleBitset {
public:
	SimpleBitset();
	std::size_t size() const;
	bool get(std::size_t pos) const;
	void set(std::size_t pos, bool b);
private:
	using BitStorage = unsigned long;
	BitStorage bits;
	static const std::size_t
	    BPW = std::numeric_limits<BitStorage>::digits;
};

#endif
