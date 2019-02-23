#include <ctime>  // time and localtime
#include "date.h"
#include <string>
#include <ios>
#include <ostream>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;
using std::ostream;
using std::endl;
using std::cout;
using std::istream;
using std::ios_base;

int Date::daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() {
	time_t timer = time(0); // time in seconds since 1970-01-01
	tm* locTime = localtime(&timer); // broken-down time
	year = 1900 + locTime->tm_year;
	month = 1 + locTime->tm_mon;
	day = locTime->tm_mday;
}

Date::Date(int y, int m, int d) {
	if(y > 0 && m >= 1 && m <= 12){
		if(d > 0 && d <= daysPerMonth[m - 1]){
			year = y;
			month = m;
			day = d;
		}
	}else{
		throw "Invalid date";
	}
}

int Date::getYear() const {
	return year;
}

int Date::getMonth() const {
	return month;
}

int Date::getDay() const {
	return day;
}

void Date::next() {
	if(getDay() == daysPerMonth[getMonth() - 1]){
		day = 1;
		if(getMonth() == 12){
			++year;
			month = 1;
		}
	}else{
		++day;
	}
}


ostream& operator<<(ostream& stream, const Date& date){
	string month;
	string day;
	if(date.getMonth() < 10){
		month = "0" + to_string(date.getMonth());
	}else{
		month = to_string(date.getMonth());
	}
	if(date.getDay() < 10){
		day = "0" + to_string(date.getDay());
	}else{
		day = to_string(date.getDay());
	}
	stream << to_string(date.getYear()) << "-";
	stream << month << "-";
	stream << day;
	return stream;
}

istream& operator>>(istream& stream, Date& date){
	string input;
	getline(stream,input);
	size_t n = count(input.begin(), input.end(), '-');
	if(n == 2){
		stringstream ss(input);
		int number;
		char dash;
		ss >> number;
		if(!date.isLegitY(date, number)){
			stream.setstate (ios_base::failbit);
			return stream;
		}

		ss >> dash;
		if(dash != '-'){
			stream.setstate (ios_base::failbit);
			return stream;
		}
		
		ss >> number;
		if(!date.isLegitM(date, number)){
			stream.setstate (ios_base::failbit);
			return stream;
		}

		ss >> dash;
		if(dash != '-'){
			stream.setstate (ios_base::failbit);
			return stream;
		}

		ss >> number;
		if(!date.isLegitD(date, number)){
			stream.setstate (ios_base::failbit);
			return stream;
		}

	}
	return stream;
}

bool Date::isLegitY(Date& date, const int aYear) {
	if(aYear > 0){
		date.year = aYear;
		return true;
	}else{
		return false;
	}

}

bool Date::isLegitM(Date& date, const int aMonth) {
	if(aMonth > 0 && aMonth <= 12){
		date.month = aMonth;
		return true;
	}else{
		return false;
	}
}

bool Date::isLegitD(Date& date, const int aDay) {
	if(aDay > 0){
		if(aDay <= daysPerMonth[date.getMonth() - 1]){
			date.day = aDay;
			return true;
		}
	}else{
		return false;
	}
}