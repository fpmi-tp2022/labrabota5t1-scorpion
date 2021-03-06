// autoparkUI.h
// lab5

#pragma once
#include <string>
using namespace std;

// Get data for inserting into a table
string getIndertData(string& table, string& photoFileName, string& driverServiceNumber);

// Get data for deleting record from table
string getDeleteData(string& table, string& column);

// Get data for updating record in table
string getUpdateValue(string& table, string& column, string& value, string& columnToChange);

// Get data for selecting all table
string getSelectData(int& columnNumber, string& columnNames);

// Get driver service number
string getDriverServiceNumber(istream& in = cin);

// Get car number
string getCarNumber(istream& in = cin);

// Get period
string getPeriodData(istream& in = cin);

// Print menu for admin
void printAdminMenu();

//Print menu for driver
void printDriverMenu();

