#include <iostream>
#include "../includes_usr/fileIO.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>
#include <sstream>
#include "../includes_usr/datastructures.h"
#include "../includes_usr/constants.h"
using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */


std::string filename;

//put the above in an includes folder



//try



int loadBooks(std::vector<book> &books, const char* filename)
{


	books.clear();

ifstream myfile;
myfile.open(filename);


if (!myfile.is_open()){
return COULD_NOT_OPEN_FILE;
}

std::string line;
book myData;
stringstream sstream;
int stateObject;






while (!myfile.eof()){


//myData.title = "";
//myData.state = UNKNOWN;
//myData.author = "";
//myData.loaned_to_patron_id = 0;


	


	std::cout << "Test";
	std::string buffer;
	//int buffer2;
	
	

	getline(myfile, line);
	
	
	
	std::cout << myData.book_id;
	//get the ID
	






	getline(sstream, buffer, ',');
	std::cout << "Here1";
	myData.book_id = stoi(buffer);
	//get name (if empty string then missing value)
	



	getline(sstream, buffer, ',');
	myData.title = buffer;
	//get author
	


	getline(sstream, buffer, ',');
	myData.author = buffer;

	getline(sstream, buffer, ',');
	stateObject = stoi(buffer);
	myData.state = static_cast<book_checkout_state>(stateObject);
	getline(sstream, buffer, ',');

	std::cout << "Here3";
	myData.loaned_to_patron_id = stoi(buffer);//get a line from the file
	sstream.str(line);
	




	//finally add to array
	books.push_back(myData);
	//clear stream so it will work for next read
	sstream.clear();
}
if (line.length() == 0){
		return NO_BOOKS_IN_LIBRARY;
}
		
if (books.size() == 0){
	return NO_BOOKS_IN_LIBRARY;
}

return SUCCESS;
}



/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	ofstream myfile;


	myfile.open(filename);

	if (!myfile.is_open()){
	return COULD_NOT_OPEN_FILE;
	}

	if (books.size() == 0){
	return NO_BOOKS_IN_LIBRARY;
	}



	string mybooks;
	for (unsigned int var = 0; var < books.size(); var++) {
	mybooks = to_string(books[var].book_id) + "," + books[var].title + "," + books[var].author + "," + to_string(books[var].state) + "," + to_string(books[var].loaned_to_patron_id);


	myfile<<mybooks<<std::endl;
	}

	if (myfile.is_open()){
	myfile.close();
	}



return SUCCESS;
}



/*bool diff_files(TMP FILE, BOOKFILE){
	if (TMP FILE != BOOKFILE){
		return SUCCESS;
	}
}
*/

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename){


	//clear Patron

patrons.clear();


ifstream myfile;



myfile.open(filename);



std::string line;
std::string buffer;
book myData;
stringstream ss;
//patron




while (!myfile.eof()){




patron patronInfo;


patronInfo.name = "";

patronInfo.patron_id = UNINITIALIZED;

patronInfo.number_books_checked_out = NONE;




getline(myfile, line);
if (line.length() == 0){
	return NO_PATRONS_IN_LIBRARY;//get a line from the file
}

ss.str(line);
getline(ss, buffer, ',');
patronInfo.patron_id = stoi(buffer);


//get name (if empty string then missing value)
getline(ss, buffer, ',');
patronInfo.name = buffer;

//get NBCO
getline(ss, buffer, ',');
patronInfo.number_books_checked_out = stoi(buffer);


//get rid of the old values










//finally add to file
patrons.push_back(patronInfo);

//clear stream so it will work for next read
ss.clear();
}




if (patrons.size() == 0){
return NO_PATRONS_IN_LIBRARY;
}

return SUCCESS;
}

/* seriali#include "datastructures.h"zes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{


ofstream myfile;


myfile.open(filename);



if (!myfile.is_open()){
return COULD_NOT_OPEN_FILE;
}

if (patrons.size() == 0){
return NO_PATRONS_IN_LIBRARY;
}



string mydata;



for (unsigned int var = 0; var < patrons.size(); ++var) {
mydata = to_string(patrons[var].patron_id) + "," + patrons[var].name + "," + to_string(patrons[var].number_books_checked_out);
myfile<<mydata<<std::endl;
}

if (myfile.is_open()){
myfile.close();
}

   return SUCCESS;
}
