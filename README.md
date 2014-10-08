call-records
============

This is an extension of the call-stats projects with an OOP architecture and added functionality. It stores, processes, performs searches, adds, removes, and outputs data on a database of call records for cell phone numbers. As many new records as needed may be added. Records for a number may be removed as well. The search shows all of the records for one particular number. It accepts a data file as input, and can output a new data file after work has been done to it. 

The call records are entirely encapsulated in an object, including new private and public state members/data and methods to carry out the operations mentioned above, in addition to the call_record structure from call-stats2, which are stored in the new object in a dynamic array. Note, like its predecessor, the size of these records are unbounded as it can be dynamically resized. The driver program simply allows the user to choose from operations to carry out on the database. The information is therefore hidden/protected from the driver.

The repository contains sample "call_data.txt" and "weekly_call_info.txt" files.