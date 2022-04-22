// autoparkDB.cpp
// lab5

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <string>
#include "../include/autoparkDB.h"
using namespace std;

// Insert data into a table
void insert(sqlite3 *db, string table, string insertStr)
{
    char *err_msg = 0;
    string sql = "INSERT INTO " + table + " VALUES(" + insertStr + ");";
    
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        return;
    }
}
