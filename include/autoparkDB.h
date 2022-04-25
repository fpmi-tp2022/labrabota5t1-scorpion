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

// Print selected records
void printSelect(sqlite3_stmt *res, int count);

// Select all records from a table
void selectAllRecords(sqlite3 *db, string table, int count);

// Select and print orders by driver and period
void getOrdersByDriver(sqlite3 *db, string driverServiceNumber, string period);

// Get and print total mileage of a car
void getMileageByCar(sqlite3 *db, string carNumber);

// Get and print total weight of transported goods by car
void getTransportedWeightByCar(sqlite3 *db, string carNumber);

// Get and print total number of trips, total weight of transported goods and total sum
// of earned money of all drivers
void getNumOfTripsTransportedWeightEarningsOfAllDrivers(sqlite3 *db);

// Get and print total number of trips by driver
void getNumOfTripsByDriver(sqlite3 *db, string driverServiceNumber);

// Get and print total weight of transported goods by driver
void getTransportedWeightByDriver(sqlite3 *db, string driverServiceNumber);

// Get and print total sum of earned money by driver
void getEarningsByDriver(sqlite3 *db, string driverServiceNumber);

// Get and print information about a driver with min number of trips
void getDriverWithMinTripsNumInfo(sqlite3 *db);

// Get and print information about a car with max mileage
void getCarWithMaxMileage(sqlite3 *db);
