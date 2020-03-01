#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>
#include "../includes_usr/fileIO.h"
#include "../includes_usr/datastructures.h"
#include "../includes_usr/constants.h"
#include "../includes_usr/library.h"


using namespace std;

//NOTE: please ensure patron and book data are loaded from disk before calling the following
//NOTE: also make sure you save patron and book data to disk any time you make a change to them
//NOTE: for files where data is stored see constants.h BOOKFILE and PATRONFILE

/*
 * clear books and patrons containers
 * then reload them from disk 
 */
//make vectors like the ones in fileIO
std::vector<book> books;
std::vector<patron> patrons;

void reloadAllData(){

loadPatrons(patrons, PATRONFILE.c_str());


loadBooks(books, BOOKFILE.c_str());


}












/* checkout a book to a patron
 * first load books and patrons from disk
 * make sure patron enrolled (patronid is assigned to a patron in patrons container)
 * make sure book in collection (bookid is assigned to a book in books container)
 * 
 * see if patron can check out any more books 
 * 	if not return TOO_MANY_OUT patron has the MAX_BOOKS_ALLOWED_OUT
 * 	
 * if so then check the book out to the patron, set the following fields for the book in the
 * books container
 * book.loaned_to_patron_id = patronid;
 * book.state = OUT;
 * 
 * Finally save the contents of the books and patrons containers to disk
 * 
 * returns SUCCESS checkout worked
 *         PATRON_NOT_ENROLLED
 * 		   BOOK_NOT_IN_COLLECTION
 *         TOO_MANY_OUT patron has the max number of books allowed checked out
 */
int checkout(int bookid, int patronid){

reloadAllData();

bool bookExistsInBookfile = false;

bool patronCanCheckout = true;

bool patronExists = false;

for (unsigned int var = 0; var < books.size(); var++){
	if (bookid == books[var].book_id){
		bookExistsInBookfile = true;
	}




}

for (unsigned int var = 0; var < patrons.size(); var++){
	if (patronid == patrons[var].patron_id){
			patronExists = true;
		}

		if (patrons[var].number_books_checked_out == MAX_BOOKS_ALLOWED_OUT){
			patronCanCheckout = false;
			break;

		}
}

if (bookExistsInBookfile == false){
	return BOOK_NOT_IN_COLLECTION;
}

if (patronCanCheckout ==false){
	return TOO_MANY_OUT;

}

if (patronExists == false){
	return PATRON_NOT_ENROLLED;
}

if (books[bookid].state != IN){
	return BOOK_NOT_IN_COLLECTION;

}

books[bookid].loaned_to_patron_id = patronid;
//checked out:
books[bookid].state = OUT;
//increases how many books the patron has out:
patrons[patronid].number_books_checked_out += 1;

//put changes into respective files
//check:

saveBooks(books, BOOKFILE.c_str());
savePatrons(patrons, PATRONFILE.c_str());
	return SUCCESS;
}

/* check a book back in 
 * first load books and patrons from disk
 * make sure book in collection (bookid is assigned to a book in books container)
 *  	
 * if so find the the patron the book is checked out to and decrement his/hers number_books_checked_out
 * then check the book back in by marking the book.loaned_to_patron_id = NO_ONE and the book.state = IN;
 
 * Finally save the contents of the books and patrons containers to disk
 * 
 * returns SUCCESS checkout worked
 * 		   BOOK_NOT_IN_COLLECTION
 */
int checkin(int bookid){

reloadAllData();

//starts with the book out of the book file
bool Book_Exists = false;

for (unsigned int var = 0; var < books.size(); var++){

	if (bookid == books[var].book_id){
		Book_Exists = true;
	}


}

if (!Book_Exists){
	return BOOK_NOT_IN_COLLECTION;
}

//return the Patron who has the book.

int PatronID = books[bookid].loaned_to_patron_id;

//decrement number of books checked out for patron:

patrons[PatronID].number_books_checked_out -= 1;

//mark book as not loaned and book's state as IN the books vector

books[bookid].loaned_to_patron_id = NO_ONE;

books[bookid].state = IN;


//save contents of books and patrons into files

saveBooks(books, BOOKFILE.c_str());

savePatrons(patrons, PATRONFILE.c_str());

	return SUCCESS;
}

/*
 * enroll a patron, duplicate names are fine as patrons are uniquely identified by their patronid
 * first load books and patrons from disk
 * create a patron object, initialize its fields as appropriate, assign him/her the nextPatronID
 * then push the patron onto the patrons container
 * save all changes to the patrons container to disk
 * return 
 *    the patron_id of the person added
 */
int enroll(std::string &name){

int nextPatronID = UNINITIALIZED;




//load books and patrons from disk:
reloadAllData();

//make PatronObject:


patron patronObject;

patronObject.name = name;


nextPatronID = patrons.size();
//Initializes the ID of the first member, so all other IDs can come after that accordingly
if (patrons.size()== 0){
	nextPatronID = 0;

}

	//patronID should equal its place on the patron list.

patronObject.patron_id = nextPatronID;

//set NBCO to 0, since patron has not checked out books yet

patronObject.number_books_checked_out = NONE;

//push patron onto list and save the changes

patrons.push_back(patronObject);

savePatrons(patrons, PATRONFILE.c_str());

return patronObject.patron_id;
}






//bool diff_files(string testfile, s)

/*
 * the number of books in the books container
 * (ie. if 3 books returns 3)
 * 
 */
int numbBooks(){

reloadAllData();
	int numberOfBooks = 0;

			for (unsigned int i = 0; i < books.size(); i++){
				numberOfBooks += 1;
				}
return numberOfBooks;
}

/*
 * the number of patrons in the patrons container
 * (ie. if 3 patrons returns 3)
 */
int numbPatrons(){

	reloadAllData();

int numberOfPatrons = 0;

			for (unsigned int i = 0; i < patrons.size(); i++){
					numberOfPatrons += 1;
				}



return numberOfPatrons;
}

/*the number of books patron has checked out
 *
 *returns a positive number indicating how many books are checked out 
 *        or PATRON_NOT_ENROLLED         
 */
int howmanybooksdoesPatronHaveCheckedOut(int patronid){




if (patrons[patronid].number_books_checked_out == MAX_BOOKS_ALLOWED_OUT){
	return MAX_BOOKS_ALLOWED_OUT;
}


return SUCCESS;
}


/* search through patrons container to see if patronid is there
 * if so returns the name associated with patronid in the variable name
 * 
 * returns SUCCESS found it and name in name
 *         PATRON_NOT_ENROLLED no patron with this patronid
 */
int whatIsPatronName(std::string &name,int patronid){


bool PatronExists = false;



for (unsigned int var = 0; var < patrons.size(); var++){
if (patronid == patrons[var].patron_id && name == patrons[var].name){
PatronExists = true;
}


}
if (PatronExists == false){
	return PATRON_NOT_ENROLLED;
}

	return SUCCESS;
}
