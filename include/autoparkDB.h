// autoparkDB.h
// lab5

#pragma once
#include <string>
using namespace std;

// Insert data into a table
void insert(sqlite3 *db, string table, string insertStr);

// Delete data from a table
void deleteRecord(sqlite3 *db, string table, string column, string deleteValue);

// Update record in a table
void update(sqlite3 *db, string table, string column, string value, string columnToChange, string newValue);

// Print Selected records
void printSelect(sqlite3_stmt *res, int count);

// Select all records from a table
void selectAllRecords(sqlite3 *db, string table, int count);