// autoparkDB.cpp
// lab5

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string>
#include <cstring>
#include "../include/autoparkDB.h"
using namespace std;

// Insert image into a table (update table)
void insertImage(sqlite3 *db, string fileName, string driverServiceNumber)
{
    FILE *fp = fopen(fileName.c_str(), "rb");
    
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open image file\n");
        return;
    }
    
    fseek(fp, 0, SEEK_END);
    
    if (ferror(fp))
    {
        fprintf(stderr, "fseek() failed\n");
        int r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        return;
    }
    
    int flen = ftell(fp);
    
    if (flen == -1)
    {
        perror("error occurred");
        int r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        return;
    }
    
    fseek(fp, 0, SEEK_SET);
    
    if (ferror(fp))
    {
        fprintf(stderr, "fseek() failed\n");
        int r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        return;
    }
    
    char data[flen+1];
    int size = fread(data, 1, flen, fp);
    
    if (ferror(fp))
    {
        fprintf(stderr, "fread() failed\n");
        int r = fclose(fp);
        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }
        return;
    }
    
    int r = fclose(fp);
    
    if (r == EOF) {
        fprintf(stderr, "Cannot close file handler\n");
    }
    
    char *err_msg = 0;
    sqlite3_stmt *pStmt;
    
    string sql = "update drivers set photo=(?) where service_number='" + driverServiceNumber + "'";
    
    int rc = sqlite3_prepare(db, sql.c_str(), -1, &pStmt, 0);
    
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    sqlite3_bind_blob(pStmt, 1, data, size, SQLITE_STATIC);
    
    rc = sqlite3_step(pStmt);
    if (rc != SQLITE_DONE)
    {
        printf("execution failed: %s", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(pStmt);
}

// Insert data into a table
void insert(sqlite3 *db, string table, string insertStr, string photoFileName, string driverServiceNumber)
{
    string insertStrCopy = insertStr;
    if(table == "completed_orders")
    {
        char* insertStr2 = (char*)insertStrCopy.c_str();
        char* insertParam;

        insertParam = strtok(insertStr2, ",'");
        for(int i = 1; i <=6; i++)
        {
            insertParam = strtok(NULL, ",'");
        }
        string carNumber = insertParam;
        
        for(int i = 1; i <=4; i++)
        {
            insertParam = strtok(NULL, ",'");
        }
        
        
        string cargoWeight = insertParam;
        
        if(!checkCargoWeight(db, carNumber, cargoWeight))
        {
            cout << "Вес груза превышает грузоподъемность машины. Заказ не был добавлен\n";
            return;
        }
    }
    
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
    
    if (driverServiceNumber != "")
    {
        insertImage(db, photoFileName, driverServiceNumber);
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

// Print selected records
void printSelect(sqlite3_stmt *res, int columnNumber)
{
    while(true)
    {
        int step = sqlite3_step(res);
        if (step == SQLITE_ROW)
        {
            for(int i = 0; i < columnNumber; i++)
            {
                printf("|%s", sqlite3_column_text(res, i));
            }
            printf("|\n");
        }
        else
        {
            break;
        }
    }
}

// Select all records from a table
void selectAllRecords(sqlite3 *db, string table, int columnNumber)
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
    
    printSelect(res, columnNumber);
    sqlite3_finalize(res);
}

// Select and print orders by driver and period
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

// Get and print total mileage of a car
void getMileageByCar(sqlite3 *db, string carNumber, ostream& outStream)
{
    sqlite3_stmt *res;
    string sql = "SELECT sum(kilometrage) from completed_orders where car_number='" + carNumber + "'";
    
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    int step = sqlite3_step(res);
    
    const unsigned char* kilometrage;
    if (step == SQLITE_ROW)
    {
        kilometrage = sqlite3_column_text(res, 0);
    }
    
    sql = "SELECT mileage from cars where car_number='" + carNumber + "'";
    
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    step = sqlite3_step(res);
    
    const unsigned char* mileage;
    if (step == SQLITE_ROW)
    {
        mileage = sqlite3_column_text(res, 0);
    }
    
    int kilometrageInt = stoi((char*)kilometrage);
    int mileageInt = stoi((char*)mileage);
    
    outStream << "Общий пробег:" << endl;
    outStream << kilometrageInt + mileageInt << endl;

    sqlite3_finalize(res);
}

// Get and print total weight of transported goods by car
void getTransportedWeightByCar(sqlite3 *db, string carNumber, ostream& out)
{
    sqlite3_stmt *res;
    string sql = "SELECT sum(cargo_weight) from completed_orders where car_number='" + carNumber + "'";
    
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    int step = sqlite3_step(res);
    
    const unsigned char* totalWeight;
    if (step == SQLITE_ROW)
    {
        totalWeight = sqlite3_column_text(res, 0);
    }
    
    out << "Общая масса перевезенных грузов:" << endl;
    out << totalWeight << endl;
    
    sqlite3_finalize(res);
}

// Get and print total number of trips, total weight of transported goods and total sum
// of earned money of all drivers
void getNumOfTripsTransportedWeightEarningsOfAllDrivers(sqlite3 *db)
{
    sqlite3_stmt *res;
    string sql = "SELECT service_number, last_name from drivers";
    
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    int step = sqlite3_step(res);
    while (step == SQLITE_ROW)
    {
        string driverServiceNumber = (char*)sqlite3_column_text(res, 0);
        cout << "\tТабельный номер: " << driverServiceNumber << endl;
        cout << "\tФамилия водителя: " << sqlite3_column_text(res, 1) << endl;
        getNumOfTripsByDriver(db, driverServiceNumber);
        getTransportedWeightByDriver(db, driverServiceNumber);
        getEarningsByDriver(db, driverServiceNumber);
        step = sqlite3_step(res);
    }
    
    sqlite3_finalize(res);
}

// Get and print total number of trips by driver
void getNumOfTripsByDriver(sqlite3 *db, string driverServiceNumber, ostream& out)
{
    sqlite3_stmt *res;
    string sql = "SELECT count(id) from completed_orders where driver_service_number='" + driverServiceNumber + "'";
    
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    int step = sqlite3_step(res);
    
    const unsigned char* numTrips;
    if (step == SQLITE_ROW)
    {
        numTrips = sqlite3_column_text(res, 0);
    }
    
    out << "Общее количество поездок: ";
    out << numTrips << endl;
    
    sqlite3_finalize(res);
}

// Get and print total weight of transported goods by driver
void getTransportedWeightByDriver(sqlite3 *db, string driverServiceNumber, ostream& out)
{
    sqlite3_stmt *res;
    string sql = "SELECT sum(cargo_weight) from completed_orders where driver_service_number='" + driverServiceNumber + "'";
    
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    int step = sqlite3_step(res);
    
    const unsigned char* totalWeight;
    if (step == SQLITE_ROW)
    {
        totalWeight = sqlite3_column_text(res, 0);
    }
    
    out << "Общая масса перевезенных грузов: ";
    out << totalWeight << endl;
    
    sqlite3_finalize(res);
}

// Get and print total sum of earned money by driver
void getEarningsByDriver(sqlite3 *db, string driverServiceNumber, ostream& out)
{
    sqlite3_stmt *res;
    string sql = "SELECT sum(cost) from completed_orders where driver_service_number='" + driverServiceNumber + "'";
    
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    int step = sqlite3_step(res);
    
    const unsigned char* totalCost;
    if (step == SQLITE_ROW)
    {
        totalCost = sqlite3_column_text(res, 0);
    }
    
    double totalCostInt = atof((char*)totalCost);
    totalCostInt *= 0.2;
    
    out << "Общая сумма заработанных денег: ";
    out << totalCostInt << endl;
    
    sqlite3_finalize(res);
}

// Get and print information about a driver with min number of trips
void getDriverWithMinTripsNumInfo(sqlite3 *db)
{
    sqlite3_stmt *res;
    string sql = "SELECT count(*), driver_service_number from completed_orders group by driver_service_number order by count(*) asc";
    
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    int step = sqlite3_step(res);
    int min = stoi((char*)sqlite3_column_text(res, 0));
    
    cout << "Водители, выполнившие наименьшее количество поездок (min = " << min << ")" << endl;
    string columnNames = "|service_number|last_name|category|work_experience|address|birth_year|cars_car_number|";
    cout << columnNames << endl;
    
    int columnNumber = 7;
    
    while (step == SQLITE_ROW)
    {
        if  (stoi((char*)sqlite3_column_text(res, 0)) == min)
        {
            string driverServiceNumber = (char*)sqlite3_column_text(res, 1);
            sql = "SELECT * from drivers where service_number='" + driverServiceNumber + "'";
            
            sqlite3_stmt *resDriver;
            rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &resDriver, 0);
            if (rc != SQLITE_OK)
            {
                cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
                return;
            }
            
            int step2 = sqlite3_step(resDriver);
            if (step2 == SQLITE_ROW)
            {
                for(int i = 0; i < columnNumber; i++)
                {
                    printf("|%s", sqlite3_column_text(resDriver, i));
                }
                printf("|\n");
            }
            getEarningsByDriver(db, driverServiceNumber);
            sqlite3_finalize(resDriver);
        }
        else
        {
            break;
        }
        step = sqlite3_step(res);
    }
    
    sqlite3_finalize(res);
}

// Get and print information about a car with max mileage
void getCarWithMaxMileage(sqlite3 *db)
{
    sqlite3_stmt *res;

    string sql = "SELECT   (cars.mileage + coalesce (SUM( completed_orders.kilometrage),0)) AS total_kilometrage, cars.car_number AS num FROM cars LEFT OUTER JOIN completed_orders  ON cars.car_number = completed_orders.car_number GROUP BY cars.car_number ORDER BY total_kilometrage DESC";
    
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return;
    }
    
    int step = sqlite3_step(res);
    
    string maxMileage, curMileage;
    char* carNumber;
    sqlite3_stmt *resCars;
    
    if(step == SQLITE_ROW)
    {
        maxMileage = (char*)sqlite3_column_text(res, 0);
        cout << "Максимальный пробег: " << maxMileage << "\n";
        cout << "Машины с максимальным пробегом:\n";
        cout << "car_number|brand|mileage|capacity\n";
    }
    
    curMileage = maxMileage;
    while (step == SQLITE_ROW)
    {
        curMileage =(char*)sqlite3_column_text(res, 0);
        if(    curMileage != maxMileage)
        {
            break;
        }
        carNumber = (char*)sqlite3_column_text(res, 1);
        sql = "SELECT * FROM cars WHERE car_number='";
        sql += carNumber;
        sql += "'";
        
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &resCars, 0);
        if (rc != SQLITE_OK)
        {
            cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
            return;
        }
        
        printSelect(resCars, 4);
        
        sqlite3_finalize(resCars);
        
        step = sqlite3_step(res);
    }
    

    sqlite3_finalize(res);
}

//  Checks whether the weight of cargo daesn't exceed car's capacity
bool checkCargoWeight(sqlite3 *db, string carNumber, string cargoWeight)
{
    string sql = "SELECT capacity FROM cars WHERE car_number='" + carNumber+ "'";
    
    sqlite3_stmt *res;
    
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    
    int step = sqlite3_step(res);
    
    int carCapacity;
    if (step == SQLITE_ROW)
    {
        carCapacity = atoi((char*)sqlite3_column_text(res, 0));
    }
    
    sqlite3_finalize(res);
    
    if((double)carCapacity < stof(cargoWeight.c_str()))
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Get and print sum of earned money by driver for specified period
void getEarningsByDriverByPeriod(sqlite3 *db, string driverServiceNumber, string startDate, string endDate, ostream& out)
{
    sqlite3_stmt *res;
    string sql = "SELECT sum(cost) FROM completed_orders WHERE driver_service_number='" + driverServiceNumber + "' AND (date BETWEEN '" + startDate + "' AND '" + endDate + "')";
        
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return;
    }
        
    int step = sqlite3_step(res);
        
    double earnings;
    if (step == SQLITE_ROW)
    {
        earnings = atof((char*)sqlite3_column_text(res, 0));
    }
        
    earnings *= 0.2;
        
    out << "Сумма заработанных денег за период с " << startDate << " по " << endDate << ": \n";
    out << earnings << endl;
        
    sqlite3_finalize(res);
}

// Get, print and save to table earnings sum of earned money by all drivers for specified period
void getEarningsAllDriversByPeriod(sqlite3 *db, string startDate, string endDate)
{
    
    string sql = "SELECT driver_service_number, driver_last_name, sum(cost) FROM completed_orders  WHERE (date BETWEEN '" + startDate + "' AND '" + endDate + "') GROUP BY driver_service_number";
    
    sqlite3_stmt *res;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return;
    }
        
    int step = sqlite3_step(res);
    
    sql = "DELETE FROM earnings;";
    
    char* err_msg = 0;
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " <<err_msg << endl;
        sqlite3_free(err_msg);
        return;
    }
    
    double earnings;
    string driverLastName;
    string driverNumber;
    
    cout << "Сумма заработанных денег за период с " << startDate << " по " << endDate << ": \n";
    cout << "driver_service_number|driver_last_name|earned_sum\n";
    while (step == SQLITE_ROW)
    {
        driverNumber = (char*)sqlite3_column_text(res, 0);
        driverLastName = (char*)sqlite3_column_text(res, 1);
        earnings = atof((char*)sqlite3_column_text(res, 2));
        earnings *= 0.2;
        
        cout << driverNumber << "|" << driverLastName << "|" << earnings << "\n";
        
        char* sqlChar;
        
        sql = "INSERT INTO earnings VALUES ('" + driverLastName + "', '" + driverLastName + "', '" + to_string(earnings) + "')";
        
        err_msg = 0;
        rc = sqlite3_exec(db, sql.c_str(), 0, 0, &err_msg);
        
        if (rc != SQLITE_OK)
        {
            cerr << "SQL error: " <<err_msg << endl;
            sqlite3_free(err_msg);
            return;
        }
        
        step = sqlite3_step(res);
    }
        
        
    sqlite3_finalize(res);
}


