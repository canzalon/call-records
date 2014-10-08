/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Project:	call-records
File:       rcalls.cpp
Author:     Christopher M. Anzalone		

Description: This file contains the implementation for the RCALLS class.
  Functions:
              operator<<    (#OS)   -   end_Calls              (#EC)
              is_Full       (#IF)   -   ~RCALLS                (#DCON)
              is_Empty      (#IE)   -   search_DB              (#SD)
              RCALLS        (#DEF)  -   process_data_DB        (#PD)
              call_Stats    (#CS)   -   process_data_Single    (#PS)
              add_DB        (#AD)   -   double_DB              (#DD)
              remove_DB     (#RD)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*Preprocessor directives*/
#include "rcalls.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

/////////////////////////////////////////////////////////////////
//FUNCTION NAME: operator<<    (#OS)
//DESCRIPTION: This function overloads the insertion operator in
//order to output the data held in the dynamic array.
//PRECONDITIONS: The database must be declared and initialized.
//POSTCONDITIONS: All of the records currently in the database
//have been printed.
/////////////////////////////////////////////////////////////////
ostream& operator<<(ostream& out, const RCALLS& callR)
{
	/*Header for output*/
	out<<setw(16)<<left<<"Cell Phone #";
	out<<setw(8)<<left<<"Relays\t"<<"Min\t"<<"Net\t"
		<<"Rate\t"<<"Tax\t"<<"Total Cost"<<endl;

	//All records currently in database are displayed
	for (int x=0; x < callR.num; x++)
	{
		out<<callR.call_DB[x].cellNum<<"\t"
		<<callR.call_DB[x].rStat<<"\t"
		<<callR.call_DB[x].lengthMin<<"\t"
		<<callR.call_DB[x].netCost<<"\t"
		<<callR.call_DB[x].taxRate<<"\t"
		<<callR.call_DB[x].callTax<<"\t"
		<<callR.call_DB[x].tCost<<"\t"
		<<endl;
	}

	return out;
}

/////////////////////////////////////////////////////////////////
//FUNCTION NAME: is_Full    (#IF)
//DESCRIPTION: This function checks to see if the database is
//full.
//PRECONDITIONS: The database must be declared and initialized.
//POSTCONDITIONS: Either true has been returned, or
//false, depending on whether the DB is full or not.
/////////////////////////////////////////////////////////////////
bool is_Full(const RCALLS& e)	
{
	if (e.num==e.size)
		return 1;	//true; is full
	else
		return 0;	//false; is not full
}

/////////////////////////////////////////////////////////////////
//FUNCTION NAME: is_Empty    (#IE)
//DESCRIPTION: This function checks to see if the database is
//empty.
//PRECONDITIONS: The database must be declared and initialized.
//POSTCONDITIONS: Either true has been returned, or
//false, depending on whether the DB is empty or not.
/////////////////////////////////////////////////////////////////
bool is_Empty(const RCALLS& e)	
{
	if (e.num==0)
		return 1;	//true; is empty
	else
		return 0;	//false; is not empty
}

/////////////////////////////////////////////////////////////////
//FUNCTION NAME: RCALLS    (#DEF)
//DESCRIPTION: The default constructor for the RCALLS class 
//allocates dynamic memory to create the database. Afterward,
//the user is prompted for the data file. After its loaded, the
//data file is read in and then processed immediately.
/////////////////////////////////////////////////////////////////
RCALLS::RCALLS()
{
	/*allocate memory for dynamic array; initialize num, size*/
	num=0;
	size=5;
	call_DB = new call_record[size];

	/*initialize all variables in call_record struct to zero*/
	for (int x=0; x<size; x++)
	{
		call_DB[x].rStat=0.0;
		call_DB[x].lengthMin=0.0;
		call_DB[x].netCost=0.0;
		call_DB[x].taxRate=0.0;
		call_DB[x].callTax=0.0;
		call_DB[x].tCost=0.0;
	}

	/*Declaration of filestream object and file name string*/
	string filename;
	ifstream in;

	/*Input for name of file to input*/
	cout<<"\nPlease enter the filename\n"<<endl;
	cin>>filename;

	/*Open and read data from file, then close file*/
	in.open(filename.c_str());

	/*Reads file and makes room for file entries
	that exceed the max size*/
	while(!in.eof())
	{
		if (num==size)	
		{
			double_DB();
		}

		in>>call_DB[num].cellNum
		  >>call_DB[num].rStat
		  >>call_DB[num].lengthMin;
		num++;
	}

	in.close();
	
	/*Database processed after file has been read*/
	process_data_DB();

	cout<<"\nInitialization complete."<<endl;
}

/////////////////////////////////////////////////////////////////
//FUNCTION NAME: call_Stats    (#CS)
//DESCRIPTION: This function prints to the user all of the 
//information on a particular phone number, based on the number
//they asked for.
//PRECONDITIONS: One or more records must exist in the database.
//POSTCONDITIONS: All of the records for the number entered have
//been displayed to the user.
/////////////////////////////////////////////////////////////////
void RCALLS::call_Stats()
{
	if (num == 0)	/*Checks if database is empty*/
	{
		cout<<"The array is empty; there is nothing to print "<<endl;
	}
	else	/*Searches for all (if any) instances of the number*/
	{
		/*Prompt for number*/
		cout<<"Please enter the number you wish to search for."<<endl;
		cin>>prNum;

		/*Checks if the number exists*/
		int i=search_DB(prNum);

		if (i == -1)
		{
			cout <<prNum<<" is not in the database, unable to print. "<<endl;
		}
		else
		{	
			/*Searches for all instances of the number
			and displays information for each record*/
			cout<<setw(16)<<left<<"Cell Phone #";
			cout<<setw(8)<<left<<"Relays\t"<<"Min\t"<<"Net\t"
			<<"Rate\t"<<"Tax\t"<<"Total Cost"<<endl;

			int z=0;

			/*Total declarations*/
			double totalRelay=0.0, totalMinutes=0.0, totalNet=0.0, 
				totalCost=0.0, totalTax=0.0;

			/*Finds every existing entry of number and calculates totals*/
			while (z<num) 
			{
				if (call_DB[z].cellNum==prNum)
				{
					/*Existing info for phone number entry displayed*/
					cout<<" "<<call_DB[z].cellNum<<"\t"<<call_DB[z].rStat
						<<"\t"<<call_DB[z].lengthMin<<"\t"<<call_DB[z].netCost
						<<"\t"<<call_DB[z].taxRate<<"\t"<<call_DB[z].callTax
						<<"\t"<<call_DB[z].tCost<<endl;
				
					/*calculate totals of the number*/
					totalRelay=((call_DB[z].rStat)+(totalRelay));
					totalMinutes=((call_DB[z].lengthMin)+(totalMinutes));
					totalNet=((call_DB[z].netCost)+(totalNet));
					totalCost=((call_DB[z].tCost)+(totalCost));
					totalTax=((call_DB[z].callTax)+(totalTax));
				}
				z++;
			}

			/*Totals output*/
			cout<<"Totals\t\t"<<totalRelay<<"\t"<<totalMinutes<<"\t"<<totalNet
			<<" \tN/A\t"<<totalTax<<"\t"<<totalCost<<endl;
		}
	}
}

/////////////////////////////////////////////////////////////////
//FUNCTION NAME: add_DB    (#AD)
//DESCRIPTION: This function allows the user to add a new
//number, along with the number of relay stations and length of 
//call in minutes.
//PRECONDITIONS: A data file must have previously initialized
//the database.
//POSTCONDITIONS: The number and its information have been 
//processed and added to the database.
/////////////////////////////////////////////////////////////////
void RCALLS::add_DB()
{
	/*Variables of new record initialized to zero*/
	recordNew.rStat=0.0;
	recordNew.lengthMin=0.0;
	recordNew.netCost=0.0;
	recordNew.taxRate=0.0;
	recordNew.callTax=0.0;
	recordNew.tCost=0.0;

	/*User input for new record*/
	cout<<"Please input the cell number of new record"<<endl;
	cin>>recordNew.cellNum;

	cout<<"Please input number of relay stations"<<endl;
	cin>>recordNew.rStat;

	cout<<"Please input length of call"<<endl;
	cin>>recordNew.lengthMin;

	/*New record processed*/
	process_data_Single();	

	/*If database is not full, new record is added to database*/
	if (num==size)
	{
		cout<<"Database is full."<<endl;
		
		double_DB();
		
		call_DB[num++]=recordNew;
		
		cout<<"Size of database has been doubled\n"
			<<" and the new record has been added."<<endl;
	}
	else 
	{
		call_DB[num++]=recordNew;
	} 

	cout<<"Add complete."<<endl;
}

/////////////////////////////////////////////////////////////////
//FUNCTION NAME: remove_DB    (#RD)
//DESCRIPTION: This function allows the user to remove a number,
//along with all of the information for it, from the database.
//PRECONDITIONS: The number that is to be removed must first
//exist in the database.
//POSTCONDITIONS: All of the records for the number entered have
//been removed.
/////////////////////////////////////////////////////////////////
void RCALLS::remove_DB()
{
	if (num == 0)	/*Checks if database is empty*/
	{
		cout<<"The array is empty; cannot remove "<<key<<endl;
	}
	else
	{
		/*Prompt for number*/
		cout<<"Please enter the number you would like to remove from "
		<<"the database."<<endl;
		cin>>key;

		/*Checks if the number to be removed exists*/
		int i=search_DB(key);

		if (i == -1)
		{
			cout <<key<<" is not in the database, unable to remove it. "<<endl;
		}
		else
		{
			int x=0;
			
			/*Searches for all instances of the number and removes it*/
			while(x!=-1)
			{
				/*Index of number returned to x*/
				x=search_DB(key);

				/*When there are no more instances of the number, loop breaks*/
				if (x==-1)
					break;

				/*After index of number is found, it is removed here*/
				for(int j=x; j<num-1; j++)
				{
					call_DB[j]=call_DB[j+1];
				}
				num--;
			}

		}
	}
	cout<<"\nRemoval complete."<<endl;
}

/////////////////////////////////////////////////////////////////
//FUNCTION NAME: end_Calls    (#EC)
//DESCRIPTION: This function outputs all of the existing data
//into a new file, "weekly_call_info.txt"
//PRECONDITIONS: One or more records must exist in the database.
//POSTCONDITIONS: Any and all numbers in the database have been
//saved in a new file in the same directory.
/////////////////////////////////////////////////////////////////
void RCALLS::end_Calls()
{
	/*Declaration of filestream object and counter*/
	ofstream end;
	int step=0; 
	
	/*New file created and opened in program*/
	end.open("weekly_call_info.txt");
	
	/*Format output for file*/
	end.setf(ios::fixed);
	end.setf(ios::showpoint);
	end.precision(2);

	/*All records in database are copied into the file*/
	while(step<num)	
	{
		end<<call_DB[step].cellNum<<"\t"
		<<call_DB[step].rStat<<"\t"
		<<call_DB[step].lengthMin<<"\t"
		<<call_DB[step].netCost<<"\t"
		<<call_DB[step].taxRate<<"\t"
		<<call_DB[step].callTax<<"\t"
		<<call_DB[step].tCost<<"\t"
		<<endl;
		step++;
	}

	/*File closed*/
	end.close();
	
	cout<<"The database has been saved to weekly_call_info.txt"<<endl;
}

/////////////////////////////////////////////////////////////////
//FUNCTION NAME: ~RCALLS    (#DCON)
//DESCRIPTION: The destructor deallocates the memory from the
//database, sets the pointer variable equal to zero, and sets
//the remaining private data variables to zero.
/////////////////////////////////////////////////////////////////
RCALLS::~RCALLS()
{
	/*deallocate memory, get rid 
	of dangling pointer, etc*/
	delete [] call_DB;	
	call_DB = 0;	
	num=0;				
	size=0;
}

/////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////
int RCALLS::search_DB(string scan)
{
	int x=0;

	/*Searches for identical string in database and returns index*/
	for (;x<num;x++)
	{
		if (call_DB[x].cellNum==scan)
			return x;	
	}
	return -1;	//returned if no similar string is found
}

/////////////////////////////////////////////////////////////////
//FUNCTION NAME: process_data_DB    (#PD)
//DESCRIPTION: This function processes the information for each
//number in the database based on the number of relay stations
//and the length of the phone call. It is used in the default
//constructor to process the data after it has been stored.
//PRECONDITIONS: One or more records must exist in the database,
//with a value for relay stations and length in minutes.
//POSTCONDITIONS: Any and all numbers in the database have had
//their net cost, tax rate, call tax, and total cost calculated.
/////////////////////////////////////////////////////////////////
void RCALLS::process_data_DB()
{
	double rate=0.0;

	for (int track=0;track<num; track++)
	{
		/*calculate tax rate (%)*/
		if (call_DB[track].rStat>=1 && call_DB[track].rStat<=5)
			rate=1;
		else if (call_DB[track].rStat>=6 && call_DB[track].rStat<=11)
			rate=3;
		else if (call_DB[track].rStat>=12 && call_DB[track].rStat<=20)
			rate=5;
		else if (call_DB[track].rStat>=21 && call_DB[track].rStat<=50)
			rate=8;
		else if (call_DB[track].rStat>50)
			rate=12;

		/*set rate*/
		call_DB[track].taxRate=rate/100;

		/*calculate net cost*/
		call_DB[track].netCost=((call_DB[track].rStat/50)*(0.40)*(call_DB[track].lengthMin));

		/*calculate tax on call*/
		call_DB[track].callTax=(call_DB[track].netCost*(rate/100));

		/*calculate total*/
		call_DB[track].tCost=call_DB[track].netCost+call_DB[track].callTax;
	}
	
	cout<<"\nProcessing complete."<<endl;
}

/////////////////////////////////////////////////////////////////
//FUNCTION NAME: process_data_Single    (#PS)
//DESCRIPTION: This function processes the information for a new
//record submitted within the Add_DB function.
//PRECONDITIONS: A new phone number and its relay stations and 
//length of phone call in minutes must have been entered in the 
//Add_DB function.
//POSTCONDITIONS: The new phone number has had its net cost, tax
//rate, call tax, and total cost calculated and stored.
/////////////////////////////////////////////////////////////////
void RCALLS::process_data_Single()
{
	double rate=0.0;

	//calculate tax rate (%)
	if (recordNew.rStat>=1 && recordNew.rStat<=5)
		rate=1;
	else if (recordNew.rStat>=6 && recordNew.rStat<=11)
		rate=3;
	else if (recordNew.rStat>=12 && recordNew.rStat<=20)
		rate=5;
	else if (recordNew.rStat>=21 && recordNew.rStat<=50)
		rate=8;
	else if (recordNew.rStat>50)
		rate=12;
	
	//set rate
		recordNew.taxRate=rate/100;	
	//calculate net cost
		recordNew.netCost=((recordNew.rStat/50)*(0.40)*(recordNew.lengthMin));
	//calculate tax on call
		recordNew.callTax=(recordNew.netCost*(rate/100));
	//calculate total
		recordNew.tCost=recordNew.netCost+recordNew.callTax;
}

/////////////////////////////////////////////////////////////////
//FUNCTION NAME: double_DB    (#DD)
//DESCRIPTION: This function doubles the size of the database. 
//It is called whenever the number of elements has reached the 
//size limit.
//PRECONDITIONS: The database must be full. In other words, the
//num counter and size counter must be equal.
//POSTCONDITIONS: The capacity of the array has been doubled,
//leaving the previous data intact.
/////////////////////////////////////////////////////////////////
void RCALLS::double_DB()
{
	call_record *temp_DB;	//declare pointer to hold new memory

	size=size*2;	//double size

	temp_DB = new call_record[size];	//allocate new memory

	/*Place info from old d.array 
	into bottom of new d.array*/
	for (int x=0; x<num; x++)
	{
		temp_DB[x].cellNum = call_DB[x].cellNum;
		temp_DB[x].rStat = call_DB[x].rStat;
		temp_DB[x].lengthMin = call_DB[x].lengthMin;
		temp_DB[x].netCost = call_DB[x].netCost;
		temp_DB[x].taxRate = call_DB[x].taxRate;
		temp_DB[x].callTax = call_DB[x].callTax;
		temp_DB[x].tCost = call_DB[x].tCost;
	}

	delete [] call_DB;	//deallocate old memory
	call_DB = temp_DB;	//assign different mem. addy
}