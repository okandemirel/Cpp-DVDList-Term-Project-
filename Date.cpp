#include "Date.h"

Date::Date() {
	setDate("0/0/0");
}

Date::Date(string s) {
	setDate(s);
}

void Date::setDate(string s) {
	day = 0;
	month = 0;
	year = 0;
	for (int i = 0, j = 0; i < s.length(); i++) {
		if (s[i] == '/') j++;
		else switch (j)
		{
		case 0: day = day * 10 + s[i] - '0';
			break;
		case 1: month = month * 10 + s[i] - '0';
			break;
		default:  year = year * 10 + s[i] - '0';
			break;
		}

	}
}

bool Date::operator> (Date& d) const {
	if (year > d.year || (year == d.year && month > d.month) || (year == d.year && month == d.month && day > d.day)) return true;
	return false;
}

ostream& operator<< (ostream& os, const Date& d) {
	os << d.day << "/" << d.month << "/" << d.year;
	return os;
}
