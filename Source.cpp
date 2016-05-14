#include <fstream>
#include "Movie.h"

bool isDate(string);

int main(int argc, char const *argv[]) {

	Movie m[rows];
	string line;

	ifstream list("DVD_list.txt", ios::in);
	if (list.is_open()) {
		for (int i = 0; i < rows; i++) {
			getline(list, line);
			m[i].setMovie(line);
		}
		list.close();
	}
	else {
		cout << "Error: the movie file could not found." << endl;
	}

	int menu, t;
	string s, tempDate;
	Movie m1, m2;
	double tempPrice;
	Date d;
	MENU:
	cout << "(1) Search and display a movie by" << endl <<
		"(2) Compare two movies based on their price information" << endl <<
		"(3) List movies based on following genres" << endl <<
		"(4) Display Statistics" << endl <<
		"(5) Display movies after an input date" << endl <<
		"(0) Exit" << endl;

	do {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Please enter a valid menu number: ";
		cin >> menu;
	} while (menu < 0 || menu > 5 || cin.fail());

	switch (menu) {
				
	case 0: cout << "Thanks for using\n";
		goto EXIT;
		
		break;

	case 1: cout << "(1) DVD_Title" << endl <<
		"(2) ID" << endl;

		do {
			cout << "Please enter a valid sub-menu number: ";
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cin >> menu;
		} while (menu < 1 || menu > 2);

		switch (menu) {

		case 1:
			cout << "Title: ";
			cin.ignore();
			getline(cin, s);

			findbyTitle(m, s);
			break;

		case 2:
			cout << "ID: ";
			cin >> s;
			while (!isdigit(s[0])) {
				cout << "Please enter a valid ID: ";
				cin >> s;
			}
			findbyID(m, s);
			break;
		
		}
		break;

	case 2:
		cout << "First Movie ID: (Enter -1 to exit)  ";
		cin >> t;
		if (t != -1) {
			while (cin.fail() || !isID(m, t)) {
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Movie ID must a number please enter a valid ID: ";
				}
				else cout << "Movie could not be found please enter a different ID: ";
				cin >> t;
			}

			m1 = callbyID(m, t);

			cout << "Second Movie ID: ";
			cin >> t;
			while (cin.fail() || !isID(m, t)) {
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Movie ID must a number please enter a valid ID: ";
				}
				else cout << "Movie could not be found please enter different ID: ";
				cin >> t;
			}

			m2 = callbyID(m, t);

			if (m1 > m2) cout << "\"" << m1.getDvD_Title() << "\" (ID:" << m1.getID() << ") is more expensive than " << "\"" << m2.getDvD_Title() << "\" (ID:" << m2.getID() << ").\n";
			else if (m1 == m2) cout << "\"" << m1.getDvD_Title() << "\" (ID:" << m1.getID() << ") is as expensive as " << "\"" << m2.getDvD_Title() << "\" (ID:" << m2.getID() << ").\n";
			else cout << "\"" << m1.getDvD_Title() << "\" (ID:" << m1.getID() << ") is less expensive than " << "\"" << m2.getDvD_Title() << "\" (ID:" << m2.getID() << ").\n";

			break;
		}
		else {
			break;
		}

	case 3: cout << "(1) Suspense" << endl <<
		"(2) Foreign" << endl <<
		"(3) Comedy" << endl <<
		"(4) Western" << endl <<
		"(5) Music" << endl <<
		"(6) Drama" << endl;
		do {
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << "Please enter a valid sub-menu number: ";
			cin >> menu;
		} while (menu < 0 || menu > 6 || cin.fail());

		findbyGenre(m, menu);

		break;

	case 4: cout << "(1) Display number of each genres" << endl <<
		"(2) Display average price" << endl <<
		"(3) Display the number of movies whose price is greater than an input" << endl <<
		"(4) Display average price of \"Discontinued\" movies" << endl <<
		"(5) Display average price of \"Out\" movies" << endl <<
		"(6) Display average price of \"Cancelled\" movies" << endl;
		do {
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << "Please enter a valid sub-menu number: ";
			cin >> menu;
		} while (menu < 0 || menu > 6 || cin.fail());

		switch (menu) {

		case 1: genreCounter(m);
			break;

		case 2: calculateAvg(m);
			break;

		case 3:
			do {
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				cout << "Enter a valid Price: $";
				cin >> tempPrice;
			} while (tempPrice < 0 || cin.fail());
			greaterDisplay(m, tempPrice);
			break;

		case 4: calculateAvg(m, "Discontinued");
			break;

		case 5: calculateAvg(m, "Out");
			break;

		case 6: calculateAvg(m, "Cancelled");
			break;

		}
		break;

	case 5:
		cout << "Date: ";
		cin >> tempDate;
		while (!isDate(tempDate)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Please enter a valid Date: ";
			cin >> tempDate;
		}

		d.setDate(tempDate);
		findbyDate(m, d);
		break;

	}

	cout << endl;
	goto MENU;

EXIT:
	return 0;
}

bool isDate(string s) {
	int _day = 0, _month = 0, j = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '/') j++;
		else if (s[i] < '0' || s[i] > '9') return false;
		else switch (j) {
		case 0: _day = _day * 10 + s[i] - '0';
			break;
		case 1:
			if (_day < 1 || _day > 31) return false;
			_month = _month * 10 + s[i] - '0';
			break;
		case 2:
			if (_month < 1 || _month > 12) return false;
			break;
		}
	}
	if (j != 2) return false;
	return true;
}
