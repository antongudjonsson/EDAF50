#ifndef PRIMES_H
#define PRIMES_H
#include <string>

class PrimeFinder{
    public:
    PrimeFinder(int p);

    void findPrimes();
    
    /*Prints all primes in the space 0-p*/
    void printAll();

    /*Prints the largest prime in the space 0-p*/
    void printLargest();

    /*Returns a string with all numbers classified as Prime or non-prime*/
    std::string getClassified();

    std::string getPrimes();

    private:
    std::string sieve;
};
#endif