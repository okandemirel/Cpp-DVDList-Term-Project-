#include "Movie.h"

Movie::Movie() {
	setMovie("");
}

Movie::Movie(string s) {
	setMovie(s);
}

void Movie::setMovie(string s) {

	DVD_Title = "";
	Status = "";
	Price = 0.0;
	Year = 0;
	Genre = "";
	DVD_ReleaseDate.setDate("0/0/0");
	ID = 0;

	string temp = "";

	for (int i = 0, j = 0; i < s.length(); i++) {
		if (s[i] == '\t' || s[i] == '\n' || s[i] == '\r') j++;
		else switch (j) {
		case 0: DVD_Title.push_back(s[i]);
			break;
		case 1: Status.push_back(s[i]);
			break;
		case 2: temp.push_back(s[i]);
			if (s[i + 1] == '\t') {
				temp = temp.substr(1);
				Price = stod(temp);
				temp = "";
			}
			break;
		case 3: if (s[i] <= '9' && s[i] >= '0') Year = (Year * 10) + s[i] - '0';
			break;
		case 4: Genre.push_back(s[i]);
			break;
		case 5: temp.push_back(s[i]);
			if (s[i + 1] == '\t') DVD_ReleaseDate.setDate(temp);
			break;
		case 6: ID = ID * 10 + s[i] - '0';
			break;
		}
	}
}

string Movie::getDvD_Title() {
	return DVD_Title;
}

int Movie::getID() {
	return ID;
}

bool Movie::operator> (const Movie& m) const {
	bool b = (Price > m.Price) ? true : false;
	return b;
}
bool Movie::operator== (const Movie& m) const {
	bool b = (Price == m.Price) ? true : false;
	return b;
}

ostream& operator<< (ostream& os, const Movie& m) {
	if (m.Year != 0)
		os << m.DVD_Title << "\t" << m.Status << "\t" << "$" << m.Price << "\t" << m.Year << "\t" << m.Genre << "\t" << m.DVD_ReleaseDate << "\t" << m.ID;
	else
		os << m.DVD_Title << "\t" << m.Status << "\t" << "$" << m.Price << "\t" << "UNK" << "\t" << m.Genre << "\t" << m.DVD_ReleaseDate << "\t" << m.ID;

	return os;
}

bool isID(Movie* m, int j) {
	for (int i = 0; i < rows; i++) {
		if (m[i].ID == j) return true;
	}
	return false;
}

void findbyTitle(Movie* m, string s) {
	bool b = false;
	if (s.back() != '*') {
		for (int i = 0; i < rows; i++)
			if (m[i].DVD_Title.compare(s) == 0) {
				cout << m[i] << endl;
				b = true;
				break;
			}

	}
	else {
		s.pop_back();
		for (int i = 0; i < 5185; i++) {
			if (m[i].DVD_Title.find(s) == 0) {
				cout << m[i] << endl;
				b = true;
			}
		}
	}
	if (!b) cout << "Nothing is found." << endl;
}
void findbyID(Movie* m, string s) {
	bool b = false;
	if (s.back() != '*') {
		for (int i = 0, j = stoi(s); i < rows; i++)
			if (m[i].ID == j) {
				cout << m[i] << endl;
				b = true;
				break;
			}
	}
	else {
		s.pop_back();
		for (int i = 0, j = stoi(s), k; i < 5185; i++) {
			k = m[i].ID;
			while (k > j) k /= 10;
			if (k == j) {
				cout << m[i] << endl;
				b = true;
			}
		}
	}
	if (!b) cout << "Nothing is found." << endl;
}

Movie callbyID(Movie* m, int j) {
	for (int i = 0; i < rows; i++)
		if (m[i].ID == j)
			return m[i];
}
void findbyGenre(Movie* m, int j) {
	for (int i = 0; i < rows; i++)
		switch (j) {
		case 1:
			if ((int)m[i].Genre.find("Suspense") >= 0) cout << m[i] << endl;
			break;
		case 2:
			if ((int)m[i].Genre.find("Foreign") >= 0) cout << m[i] << endl;
			break;
		case 3:
			if ((int)m[i].Genre.find("Comedy") >= 0) cout << m[i] << endl;
			break;
		case 4:
			if ((int)m[i].Genre.find("Western") >= 0) cout << m[i] << endl;
			break;
		case 5:
			if ((int)m[i].Genre.find("Music") >= 0) cout << m[i] << endl;
			break;
		case 6:
			if ((int)m[i].Genre.find("Drama") >= 0) cout << m[i] << endl;
			break;
		}
}
void findbyDate(Movie* m, Date d) {
	for (int i = 0; i < rows; i++)
		if (m[i].DVD_ReleaseDate > d) cout << m[i] << endl;
}

void genreCounter(Movie* m) {
	map <string, int> genreCount;

	genreCount["Suspense/Thriller"] = 0;
	genreCount["Foreign"] = 0;
	genreCount["Comedy"] = 0;
	genreCount["Special Interest"] = 0;
	genreCount["Music"] = 0;
	genreCount["Drama"] = 0;
	genreCount["TV Classics"] = 0;
	genreCount["Late Night"] = 0;
	genreCount["Family"] = 0;
	genreCount["VAR"] = 0;
	genreCount["Documentary"] = 0;
	genreCount["Western"] = 0;
	genreCount["Sports"] = 0;
	genreCount["Horror"] = 0;
	genreCount["Animation"] = 0;
	genreCount["Mystery/Suspense"] = 0;
	genreCount["Action/Adventure"] = 0;
	genreCount["War"] = 0;
	genreCount["SciFi"] = 0;
	genreCount["Anime"] = 0;
	genreCount["Thriller"] = 0;
	genreCount["Silent"] = 0;
	genreCount["Action/Comedy"] = 0;
	genreCount["Fantasy"] = 0;
	genreCount["Exercise"] = 0;
	genreCount["Opera"] = 0;
	genreCount["Ballet"] = 0;
	genreCount["Musical"] = 0;
	genreCount["Comedy/Drama"] = 0;
	genreCount["Dance/Ballet"] = 0;
	genreCount["Software"] = 0;
	genreCount["Drama/Silent"] = 0;

	for (int i = 0; i < rows; i++) {
		genreCount[m[i].Genre]++;
	}

	cout << "The number of each genres is listed: " << endl;

	for (map<string, int>::iterator it = genreCount.begin(); it != genreCount.end(); it++)
		cout << it->first << ": " << it->second << endl;

}

void calculateAvg(Movie* m) {
	double sum = 0.0;
	for (int i = 0; i < rows; i++)
		sum += m[i].Price;
	double avg = sum / (double)rows;
	std::cout << setprecision(4);
	cout << "The average price is $" << avg << endl;
}

bool operator> (const Movie m, const double d) {
	bool b = (m.Price > d) ? true : false;
	return b;
}

void greaterDisplay(Movie* m, double d) {
	for (int i = 0; i < rows; i++)
		if (m[i].Price>d)
			cout << m[i] << endl;
}

void calculateAvg(Movie* m, string s) {
	double sum = 0.0;
	int j = 0;
	for (int i = 0; i < rows; i++)
		if (m[i].Status[0] == s[0]) {
			sum += m[i].Price;
			j++;
		}
	double avg = sum / (double)j;
	std::cout << setprecision(4);
	cout << "The average price of \"" << s << "\" movies is $" << avg << endl;
}
