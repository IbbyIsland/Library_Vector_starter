#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "../includes_usr/constants.h"
#include "../includes_usr/fileIO.h"
using namespace std;



/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */

int loadBooks(std::vector<book> &books, const char* filename) {
	books.clear();

//initiate myfile

ifstream myfile;

//Open file



myfile.open(filename);

//test case to open file




if (myfile.is_open() == false) {
		return COULD_NOT_OPEN_FILE;
	}




//intialize objects to load from
	std::string line;


	std::string token;

	stringstream ss;
	book bookObject;




	int objectState;

	while (!myfile.eof()) {

		getline(myfile, line);
		if (line.length() == 0) {
			if (books.size() == 0) {
				return NO_BOOKS_IN_LIBRARY;
			} else {
				//start reading in whatever info in the file

				continue;
			}
		}
		ss.str(line);

//initialize bookObject properties
		bookObject.title = "";

		bookObject.author = "";

		bookObject.loaned_to_patron_id = 0;

		bookObject.state = UNKNOWN;


		//get book ID
		getline(ss, token, ',');
		bookObject.book_id = stoi(token);
		//get the book title
		getline(ss, token, ',');
		bookObject.title = token;
		//get the book author
		getline(ss, token, ',');
		bookObject.author = token;
		//get the book State
		getline(ss, token, ',');
		objectState = stoi(token);
		bookObject.state = static_cast<book_checkout_state>(objectState);
		//get the patron ID


		getline(ss, token, ',');
		bookObject.loaned_to_patron_id = stoi(token);



		//push back to books file
		books.push_back(bookObject);



		//get the string ready for its next use
		ss.clear();

		//NO_BOOKS_IN_LIBRARY if there are 0 entries in books
		if (books.size() == 0) {
			return NO_BOOKS_IN_LIBRARY;
		}
	}

	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename) {


ofstream myfile;

myfile.open(filename);

	//testcase for opening file

if (myfile.is_open() == false) {
		return COULD_NOT_OPEN_FILE;
	}



//test case for bookfile.
	if (books.size() == 0) {
		return NO_BOOKS_IN_LIBRARY;
	}


	string mybooks;

	//Print  the patron info

	for (unsigned int var = 0; var < books.size(); var++) {
		mybooks = to_string(books[var].book_id) + "," + books[var].title + ","


		+ books[var].author + "," + to_string(books[var].state) + ","


		+ to_string(books[var].loaned_to_patron_id);



		myfile<<mybooks<<std::endl;
	}



	//close file
	if (myfile.is_open() == true) {
		myfile.close();
	}

	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename) {
//clear patrons

patrons.clear();

	//initialize file to be read into
ifstream myfile;

	//Attempts to open the file


myfile.open(filename);




if(myfile.is_open() == false) {
	return COULD_NOT_OPEN_FILE;}

    //just like loading books
	std::string line;


	std::string token;


	patron patronObject;


	stringstream ss;



//read in the same as loading books


while (!myfile.eof()) {
		getline(myfile, line);
		if (line.length() == 0) {
			if (patrons.size() == 0) {
				return NO_PATRONS_IN_LIBRARY;
			} else {


				//keep going with loading the real data
				continue;
			}
		}
		ss.str(line);




		patronObject.patron_id = UNINITIALIZED;


		patronObject.name = "";


		patronObject.number_books_checked_out = NONE;

		//use stoi
		getline(ss, token, ',');
		patronObject.patron_id = stoi(token);

		getline(ss, token, ',');
		patronObject.name = token;

		getline(ss, token, ',');
		patronObject.number_books_checked_out = stoi(token);

		//add patronObject back
		patrons.push_back(patronObject);




		ss.clear();
	}

	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename) {

ofstream myfile;

myfile.open(filename);

	//testCase
	if (myfile.is_open() == false) {
		return COULD_NOT_OPEN_FILE;
	}

	//testCase


	if (patrons.size() == 0) {
		return NO_PATRONS_IN_LIBRARY;
	}

	string patronObject;
	for (unsigned int var = 0; var < patrons.size(); var++) {
		patronObject = to_string(patrons[var].patron_id) + "," + patrons[var].name
				+ "," + to_string(patrons[var].number_books_checked_out);





		myfile<<patronObject<<endl;

	}

	//if the file is open, close it.
	if (myfile.is_open() == true) {
		myfile.close();
	}

	return SUCCESS;
}
