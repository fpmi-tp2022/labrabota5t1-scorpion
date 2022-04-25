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
string getSelectData(int& count);

// Get driver service number
string getDriverServiceNumber();

// Get car number
string getCarNumber();

// Get period
string getPeriodData();

// Print menu for admin
void printAdminMenu();
