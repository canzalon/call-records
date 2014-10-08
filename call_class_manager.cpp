/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Project:    call-records
File:       call_class_manager.cpp
Author:     Christopher M. Anzalone		

Description: This program stores, processes, performs searches, adds,
removes, and outputs data on a database of call records for cell phone
numbers. As many new records as needed may be added. Records for a number
may be removed as well. The search shows all of the records for one
particular number. It accepts a data file as input, and can output a new
data file after work has been done to it.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*Preprocessor directives*/
#include <iostream>
#include "rcalls.h"

using namespace std;

int main()
{
	/*Variable declarations/initialization*/
	RCALLS call_DB;
	int menu=0;

	/*Menu and switch statement for entire program*/
	while (menu!=6)
	{
		cout<<"\nPlease choose from the menu below"<<endl
			<<"\t(1) Add"<<endl
			<<"\t(2) Remove"<<endl
			<<"\t(3) Search for individual record"<<endl
			<<"\t(4) Output database to txt file"<<endl
			<<"\t(5) Print current database to screen"<<endl
			<<"\t(6) Exit program."<<endl;

		cin>>menu;
		cout<<endl;
		
		switch(menu)
		{
		case 1:
			call_DB.add_DB();		//ADD
			break;
		case 2:
			call_DB.remove_DB();	//REMOVE
			break;
		case 3:
			call_DB.call_Stats();	//SEARCH
			break;
		case 4:
			call_DB.end_Calls();	//OUTPUT DB
			break;
		case 5:
			cout<<call_DB;			//PRINT TO SCREEN 
			break;
		case 6:
			menu=6;					//EXIT
			break;
		default:
			cout<<"Incorrect value entered."<<endl;
		}
		cout<<endl;
	} 
	return 0;
}