#include <iostream>
#include <string>
#include <vector>
#include "primes.h"

using namespace std;
using std::cout;
using std::endl;

PrimeFinder::PrimeFinder(int p){
    psize = p + 1;
    if(psize <= 0){
        cout << "Size 0 is not allowed" << endl;
    }
    sieve.resize(p,'P');
    if(psize == 1){
        sieve[0] = 'C';
    }else{
        sieve[0] = sieve[1] = 'C';
    }
}
/*           1         2         3    5         
"CCPPCPCPCCCPCPCCCPCPCCCPCCCCCPCPCCCC"
  "PPCPCPCCCPCPCCCPCPCCCPCCCCCPCPCCCC"*/

void PrimeFinder::findPrimes(){
    for(int i = 0; i < sieve.size(); ++i){
        if(sieve[i] == 'P'){
            mark(i);
        }
    }
}

void PrimeFinder::mark(int n){
    for(int i = n*2; i < psize; i = i+n){
        sieve.replace(i,1,"C");
    }
}

void PrimeFinder::printAll(){
    cout << getPrimes() << endl;
}

void PrimeFinder::printLargest(){
    cout << sieve.find_last_of('P') << endl;
}

string PrimeFinder::getClassified(){
    return sieve;
}

string PrimeFinder::getPrimes(){
    vector<int> primes;
    for(int i = 0; i < sieve.size(); ++i){
        if(sieve[i] == 'P'){
            primes.push_back(i);
        }
    }
    string out;
    for(const int p : primes){
        out.append(to_string(p) + ", ");
    }
    out.erase(out.size() - 2, 2);
    return out;
}



/*int main(){
    PrimeFinder all(200);
    all.findPrimes();
    all.printAll();
    PrimeFinder largest(10000);
    largest.findPrimes();
    largest.printLargest();
}*/



