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
    if(insertStr == "")
    {
        return;
    }
    
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

// Delete data from a table
void deleteRecord(sqlite3 *db, string table, string column, string deleteValue)
{
    if(deleteValue == "")
    {
        return;
    }
    
    char *err_msg = 0;
    string sql = "DELETE FROM " + table + " where " + column + "='" + deleteValue + "';";
    
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        return;
    }
}

// Update record in a table
void update(sqlite3 *db, string table, string column, string value, string columnToChange, string newValue)
{
    if(newValue == "")
    {
        return;
    }
    
    char *err_msg = 0;
    string sql = "UPDATE " + table + " set " + columnToChange + "='" + newValue + "' where " + column + "='" + value + "';";
    
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << err_msg << endl;
        sqlite3_free(err_msg);
        return;
    }
}

// Print Selected records
void printSelect(sqlite3_stmt *res, int count)
{
    while(true)
    {
        int step = sqlite3_step(res);
        if (step == SQLITE_ROW)
        {
            for(int i = 0; i < count; i++)
            {
                printf("|%s", sqlite3_column_text(res, i));
            }
            printf("\n");
        }
        else
        {
            break;
        }
    }
}

// Select all records from a table
void selectAllRecords(sqlite3 *db, string table, int count)
{
    if(table == "")
    {
        return;
    }
    
    sqlite3_stmt *res;
    string sql = "SELECT * from " + table;
    
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    printSelect(res, count);
    sqlite3_finalize(res);
}

// Select orders by driver and period
void getOrdersByDriver(sqlite3 *db, string driverServiceNumber, string period)
{
    sqlite3_stmt *res;
    string sql = "";
    
    if(period == "all")
    {
        sql = "SELECT * from completed_orders where driver_service_number='" + driverServiceNumber + "'";
    }
    else
    {
        sql = "SELECT * from completed_orders where driver_service_number='" + driverServiceNumber + "' and date between " + period;
    }
    
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    printSelect(res, 8);
    sqlite3_finalize(res);
}
