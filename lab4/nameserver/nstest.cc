/*
 * nstest.cc: a program to test the name server implementations.
 */
#include "nameserverinterface.h"
#include "vns.h"
#include "mns.h"
#include "umns.h"
#include "hns.h"
#include <iostream>
#include <cassert>
#include <stdexcept>

using namespace std;

void test(NameServerInterface& ns) {
#if 0
	ns.insert("www.Bosse.se", 1);
	ns.insert("www.Ek.se", 2);
	assert(ns.lookup("www.Bosse.se") == 1);
	assert(ns.lookup("www.Ek.se") == 2);
	assert(ns.lookup("www.Nisse.se") == NON_EXISTING_ADDRESS);
	assert(! ns.remove("www.Nisse.se"));
	assert(ns.remove("www.Bosse.se"));
	assert(ns.lookup("www.Bosse.se") == NON_EXISTING_ADDRESS);
#else
    throw std::runtime_error{"test failed"};
#endif
}

int main() {
	/*
	 * Test the vector name server.
	 */
	VNS vns;
	test(vns);
	cout << "Vector passed ..." << endl;
	
	/*
	 * Test the map name server.
	 */
	MNS mns;
	test(mns);
	cout << "Map passed ..." << endl;
	
	/*
	 * Test the unordered map name server.
	 */
	UMNS umns;
	test(umns);
	cout << "Unordered map passed ..." << endl;
	
	/*
	 * Test the hash name server.
	 * The parameter to the constructor is the size of the
	 * hash table.
	 */
	HNS hns(4711);
	test(hns);
	cout << "Hash passed ..." << endl;
}
