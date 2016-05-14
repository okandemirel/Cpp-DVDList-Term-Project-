#include <iostream>

using namespace std;

class Date {
	int day, month, year;

public:
	Date();
	Date(string);
	void setDate(string);

	bool operator> (Date&) const;

	friend ostream& operator<< (ostream&, const Date&);
};
#pragma once
