
#include <string>
#include <sstream>
#include "date.h"
#include <string>
#include <iostream>

using std::endl;
using std::cout;
using std::istringstream;
using std::ostringstream;
using namespace std;

template<typename T>
std::string toString(const T& myObject) {
    ostringstream os;
    os << myObject;
    return os.str();
}

template<class T>
T string_cast(const string& myString) {
    istringstream is(myString);
    T t;
    is >> t;
    if(is.fail()) {
        throw std::invalid_argument("Error");
    }
    return t;
}

void tostringTest(){
    double d = 1.234;
    Date today(1995, 05, 22);
    string sd = toString(d);
    string st = toString(today);
    //string st = "";
    if(st == "1995-05-22" && sd == "1.234"){
        cout << "tostringtest: Success!" << endl;
    }else{
        cout << "tostringtest: Failed!" << endl;
        cout << "Expected: " << "1995-05-22" << endl;
        cout << "Actual:   " << st << endl;
        cout << "Expected: " << "1.234" << endl;
        cout << "Actual:   " << sd << endl;
    }
}

void stringcastTest(){
    int i = 0;
    double d;
    Date date;
    Date key(2015, 01, 10);
    try {
        i = string_cast<int>("123vrgtfd");
        d = string_cast<double>("12.34");
        date = string_cast<Date>("2015-01-10");
    } catch (std::invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }

    if(i != 123){
        cout << "stringcast: Failed!" << endl;
        cout << "Expected: " << "123" << endl;
        cout << "Actual:   " << toString(i) << endl;
    }else if(d != 12.34){
        cout << "stringcast: Failed!" << endl;
        cout << "Expected: " << "12.34" << endl;
        cout << "Actual:   " << toString(d) << endl;   
    }else if(date.getYear() != key.getYear() || date.getMonth() != key.getMonth() || date.getDay() != key.getDay()){
        cout << "stringcast: Failed!" << endl;
        cout << "Expected: " << "2015-01-10" << endl;
        cout << "Actual:   " << toString(date) << endl;
    }else{
        cout << "stringcast: Success!" << endl;
    }
}      

int main(){
    tostringTest();
    stringcastTest();
}