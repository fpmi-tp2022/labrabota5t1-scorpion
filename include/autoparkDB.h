// autoparkDB.h
// lab5

#pragma once
#include <string>
using namespace std;

// Insert data into a table
void insert(sqlite3 *db, string table, string insertStr);
