#include <iostream>
#include "primes.h"

using namespace std;
using std::cout;
using std::endl;

void testAllPrimes(){
    int p = 36;
    string key = "CCPPCPCPCCCPCPCCCPCPCCCPCCCCCPCPCCCC";
    string keyp = "2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31";
    PrimeFinder pf(p);
    pf.findPrimes();
    string found = pf.getClassified();
    string foundp = pf.getPrimes();
    if(found == key  && foundp == keyp){
        cout << "allPrimes: Success!" << endl;
        cout << "Actual:   " << foundp << endl;
        cout << "Actual:   " << found << endl;
    }else{
        cout << "allPrimes: Failed!" << endl;
        cout << "Expected: " << key << endl;
        cout << "Actual:   " << found << endl;
        cout << "Expected: " << keyp << endl;
        cout << "Actual:   " << foundp << endl;
    }
}

void testLargestPrime(){
    int p = 35;
    int key = 31;
    PrimeFinder pf(p);
    pf.findPrimes();
    string found = pf.getClassified();
    int lprime = found.find_last_of("P");
    if(key == lprime){
        cout << "largestPrime: Success!" << endl;
        cout << "Actual:   " << lprime << endl;
    }else{
        cout << "largestPrime: Failed!" << endl;
        cout << "Expected: " << key << endl;
        cout << "Actual:   " << lprime << endl;
    }
}

int main(){
    testAllPrimes();
    testLargestPrime();
}