/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Project:	call-records
File:       rcalls.h
Author:     Christopher M. Anzalone

Description: This file contains the class declaration of RCALLS. 
  Functions:
              operator<<    (#OS)   -   end_Calls              (#EC)
              is_Full       (#IF)   -   ~RCALLS                (#DCON)
              is_Empty      (#IE)   -   search_DB              (#SD)
              RCALLS        (#DEF)  -   process_data_DB        (#PD)
              call_Stats    (#CS)   -   process_data_Single    (#PS)
              add_DB        (#AD)   -   double_DB              (#DD)
              remove_DB     (#RD)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifndef RCALLS_H	//"if" RCALLS_H not defined..
#define RCALLS_H	//define RCALLS_H..

/*Preprocessor directives*/
#include <iostream>
#include <string>
using namespace std;

/*RCALLS class declaration*/
class RCALLS
{
public:

////Struct for call record types ------------------------------------
	struct call_record
	{
		string cellNum;    //cell number
		double rStat;      //relay stations
		double lengthMin;  //length in minutes
		double netCost;    //net cost
		double taxRate;    //tax rate
		double callTax;    //tax on call
		double tCost;      //total cost
	};  

////Friend Function Prototypes --------------------------------------

	//FUNCTION NAME: operator<<    (#OS)
	//DESCRIPTION: This function overloads the insertion operator in
	//order to output the data held in the dynamic array.
	//PRECONDITIONS: The database must be declared and initialized.
	//POSTCONDITIONS: All of the records currently in the database
	//have been printed.
	friend ostream& operator<<(ostream&, const RCALLS&);

	//FUNCTION NAME: is_Full    (#IF)
	//DESCRIPTION: This function checks to see if the database is
	//full.
	//PRECONDITIONS: The database must be declared and initialized.
	//POSTCONDITIONS: Either true has been returned, or
	//false, depending on whether the DB is full or not.
	friend bool is_Full(const RCALLS&);

	//FUNCTION NAME: is_Empty    (#IE)
	//DESCRIPTION: This function checks to see if the database is
	//empty.
	//PRECONDITIONS: The database must be declared and initialized.
	//POSTCONDITIONS: Either true has been returned, or
	//false, depending on whether the DB is empty or not.
	friend bool is_Empty(const RCALLS&);

////Public Member Function Prototypes -------------------------------

	//FUNCTION NAME: RCALLS    (#DEF)
	//DESCRIPTION: The default constructor for the RCALLS class 
	//allocates dynamic memory to create the database. Afterward,
	//the user is prompted for the data file. After its loaded, the
	//data file is read in and then processed immediately.
	RCALLS();

	//FUNCTION NAME: call_Stats    (#CS)
	//DESCRIPTION: This function prints to the user all of the 
	//information on a particular phone number, based on the number
	//they asked for.
	//PRECONDITIONS: One or more records must exist in the database.
	//POSTCONDITIONS: All of the records for the number entered have
	//been displayed to the user.
	void call_Stats();

	//FUNCTION NAME: add_DB    (#AD)
	//DESCRIPTION: This function allows the user to add a new
	//number, along with the number of relay stations and length of 
	//call in minutes.
	//PRECONDITIONS: A data file must have previously initialized
	//the database.
	//POSTCONDITIONS: The number and its information have been 
	//processed and added to the database.
	void add_DB();

	//FUNCTION NAME: remove_DB    (#RD)
	//DESCRIPTION: This function allows the user to remove a number,
	//along with all of the information for it, from the database.
	//PRECONDITIONS: The number that is to be removed must first
	//exist in the database.
	//POSTCONDITIONS: All of the records for the number entered have
	//been removed.
	void remove_DB();

	//FUNCTION NAME: end_Calls    (#EC)
	//DESCRIPTION: This function outputs all of the existing data
	//into a new file, "weekly_call_info.txt"
	//PRECONDITIONS: One or more records must exist in the database.
	//POSTCONDITIONS: Any and all numbers in the database have been
	//saved in a new file in the same directory.
	void end_Calls();

	//FUNCTION NAME: ~RCALLS    (#DCON)
	//DESCRIPTION: The destructor deallocates the memory from the
	//database, sets the pointer variable equal to zero, and sets
	//the remaining private data variables to zero.
	~RCALLS();

private:

////Private Member Variable Declarations ----------------------------

	//call_record pointer for DB, and variable for new records
	call_record *call_DB, recordNew; 

	//int size for current DB capacity, and num for amount of records
	int size, num;

	//string key for removal of #, string prNum for display of # 
	string key, prNum;

////Private Member (Helper) Functions -------------------------------

	//FUNCTION NAME: search_DB    (#SD)
	//DESCRIPTION: This function searches for a particular number
	//in the database and prints out all instances of it, along
	//with the rest of the information on record for it. It is used
	//within the call_Stats and remove_DB functions.
	//PRECONDITIONS: There exists one or more records in the
	//database.
	//POSTCONDITIONS: If the user-entered number exists in the
	//database, it, along with its information, has been printed to
	//the screen.
	int search_DB(string);

	//FUNCTION NAME: process_data_DB    (#PD)
	//DESCRIPTION: This function processes the information for each
	//number in the database based on the number of relay stations
	//and the length of the phone call. It is used in the default
	//constructor to process the data after it has been stored.
	//PRECONDITIONS: One or more records must exist in the database,
	//with a value for relay stations and length in minutes.
	//POSTCONDITIONS: Any and all numbers in the database have had
	//their net cost, tax rate, call tax, and total cost calculated.
	void process_data_DB();

	//FUNCTION NAME: process_data_Single    (#PS)
	//DESCRIPTION: This function processes the information for a new
	//record submitted within the Add_DB function.
	//PRECONDITIONS: A new phone number and its relay stations and 
	//length of phone call in minutes must have been entered in the 
	//Add_DB function.
	//POSTCONDITIONS: The new phone number has had its net cost, tax
	//rate, call tax, and total cost calculated and stored.
	void process_data_Single();	

	//FUNCTION NAME: double_DB    (#DD)
	//DESCRIPTION: This function doubles the size of the database. 
	//It is called whenever the number of elements has reached the 
	//size limit.
	//PRECONDITIONS: The database must be full. In other words, the
	//num counter and size counter must be equal.
	//POSTCONDITIONS: The capacity of the array has been doubled,
	//leaving the previous data intact.
	void double_DB();	

};

#endif	//end "if"