#include "bitreference.h"
#include "bitset.h"

BitReference& BitReference::operator=(bool b) {
	//
	// *** IMPLEMENT ***
	// This corresponds to the set() function in SimpleBitset.
	//
	if (b) {
		*p_bits |= 1L << pos;
	} else {
		*p_bits &= ~ (1L << pos);
	}
	return *this;
}

BitReference& BitReference::operator=(const BitReference& rhs) {
	//
	// *** IMPLEMENT ***
	// Same as operator=(bool), but the bit is picked from rhs
	//
	bool b = (rhs & (1L << pos)) != 0;
	if (b) {
		*p_bits |= 1L << pos;
	} else {
		*p_bits &= ~ (1L << pos);
	}
	return *this;
}

BitReference::operator bool() const {
	//
	// *** IMPLEMENT ***
	// This corresponds to the get() function in SimpleBitset.
	//
	return *p_bits & (1L << pos);
}
