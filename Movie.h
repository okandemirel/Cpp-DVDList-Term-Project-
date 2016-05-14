#pragma once
#include "Date.h"
#include <string>
#include <map>
#include <iomanip>

#define rows 5196

class Movie {
	string DVD_Title;
	string Status;
	double Price;
	int Year;
	string Genre;
	Date DVD_ReleaseDate;
	int ID;

public:
	Movie();
	Movie(string);
	void setMovie(string);
	string getDvD_Title();
	int getID();

	bool operator> (const Movie&) const;
	bool operator== (const Movie&) const;

	friend ostream& operator<< (ostream&, const Movie&);
	friend bool operator> (const Movie, const double);

	friend void findbyTitle(Movie*, string);
	friend void findbyID(Movie*, string);
	friend Movie callbyID(Movie*, int);
	friend void findbyGenre(Movie*, int);
	friend void findbyDate(Movie*, Date);
	friend void genreCounter(Movie*);
	friend void calculateAvg(Movie*);
	friend void calculateAvg(Movie*, string);
	friend void greaterDisplay(Movie*, double);
	friend bool isID(Movie*, int);

};
