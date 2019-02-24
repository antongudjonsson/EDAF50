/*
 * nstime.cc: performs timing tests of the lookup() function in
 * the three different name server implementations.
 */
#include "nameserverinterface.h"
#include "vns.h"
#include "mns.h"
#include "umns.h"
#include "hns.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

/* dns_record is the type of a name/address pair */

using dns_record = std::pair<HostName, IPAddress>;

/*
 * test() makes nbrSearches random searches in the name server ns for
 * names in the vector data, and computes the average search time
 * in milliseconds.
 */
double measureTime(const NameServerInterface& ns,
				   const vector<dns_record>& data,
				   int nbrSearches, int randomSeed) {
	if (nbrSearches <= 0) {
		return 0;
	}
	
	/*
	 * First, measure the administration time for the time measurement
	 * loop.
	 */
	default_random_engine re(randomSeed);
	uniform_int_distribution<unsigned int> rand(0, data.size() - 1);
	auto startTime = high_resolution_clock::now();
	for (int i = 0; i != nbrSearches; ++i) {
		int j = rand(re);
		HostName name = data[j].first;
		IPAddress address = data[j].second;
		if (address == NON_EXISTING_ADDRESS) {
			cerr << "Error: " << name << " not found" << endl;
		} else if (address != data[j].second) {
			cerr << "Error: " << name << " returned wrong address, "
			<< address << endl;
		}
	}
	auto elapsedTimeAdmin = high_resolution_clock::now() - startTime;
	
	/*
	 * Then, the same loop but this time we really search in the
	 * name server.
	 */
	re.seed(randomSeed);;
	startTime = high_resolution_clock::now();
	for (int i = 0; i != nbrSearches; ++i) {
		int j = rand(re);
		HostName name = data[j].first;
		IPAddress address = ns.lookup(name);
		if (address == NON_EXISTING_ADDRESS) {
			cerr << "Error: " << name << " not found" << endl;
		} else if (address != data[j].second) {
			cerr << "Error: " << name << " returned wrong address, "
			<< address << endl;
		}
	}
	auto elapsedTimeSearch = high_resolution_clock::now() - startTime;
	double elapsedTime =
	    duration_cast<milliseconds>(elapsedTimeSearch - elapsedTimeAdmin).count();
	return elapsedTime / nbrSearches;
}

int main() {
	/*
	 * The vector implementation.
	 */
	VNS vns;
	
	/*
	 * The map implementations.
	 */
	MNS mns;
	UMNS umns;
	
	/*
	 * The hash table implementation. The size of the hash table is
	 * a parameter to the constructor.
	 */
	HNS hns(17441);
	
	/*
	 * data is a vector containing the name/address pairs. Used by the
	 * measureTime() function.
	 */
	vector<dns_record> data;
	
	ifstream in("nameserverdata.txt");
	if (!in) {
		cerr << "Could not open data file (nameserverdata.txt)" << endl;
		exit(1);
	}
	
	/*
	 * Read the input file, store in the data vector. At the same time,
	 * insert the data into the name servers.
	 */
	cout << "Reading ..." << flush;
	HostName name;
	IPAddress nbr;
	while (in >> name >> nbr) {
		data.push_back(dns_record(name, nbr));
		vns.insert(name, nbr);
		mns.insert(name, nbr);
		umns.insert(name, nbr);
		hns.insert(name, nbr);
	}
	cout << " read " << data.size() << " words." << endl;
	
	/*
	 * Read the number used to seed the random number generator. Use
	 * any (preferably odd) number.
	 */
	cout << "Random seed: " << flush;
	int seed;
	cin >> seed;
	
	/*
	 * Measure the average search times for the four implementations.
	 * Use a small (1000) value for the number of searches in the
	 * vector implementation, a larger (1000 000) value for the other
	 * implementations. What values that are reasonable depends on
	 * your computer.
	 */
	cout << "Test vector. Number of searches: ";
	int nbrSearches;
	cin >> nbrSearches;
	double avgTime = measureTime(vns, data, nbrSearches, seed);
	cout << "Average search time (ms): " << avgTime << endl;
	
	cout << "Test map. Number of searches: ";
	cin >> nbrSearches;
	avgTime = measureTime(mns, data, nbrSearches, seed);
	cout << "Average search time (ms): " << avgTime << endl;
	
	cout << "Test unordered map. Number of searches: ";
	cin >> nbrSearches;
	avgTime = measureTime(umns, data, nbrSearches, seed);
	cout << "Average search time (ms): " << avgTime << endl;
	
	cout << "Test hash. Number of searches: ";
	cin >> nbrSearches;
	avgTime = measureTime(hns, data, nbrSearches, seed);
	cout << "Average search time (ms): " << avgTime << endl;
}
