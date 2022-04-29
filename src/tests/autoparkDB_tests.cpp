#include <iostream>
#include <gtest/gtest.h>
#include <sqlite3.h>

using namespace std;

bool checkCargoWeight(sqlite3* , string, string);
void getMileageByCar(sqlite3*, string, ostream&);
void getTransportedWeightByCar(sqlite3*, string, ostream&);
void getNumOfTripsByDriver(sqlite3*, string, ostream&);
void getTransportedWeightByDriver(sqlite3*, string, ostream&);
void getEarningsByDriver(sqlite3*, string, ostream&);
void getEarningsByDriverByPeriod(sqlite3*, string, string, string, ostream&);

TEST(checkCargoWeightFunctionTest, weightLessThanCapacity)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    EXPECT_EQ(checkCargoWeight(db, "1234XA", "12"), true) << "Weight is less than capacity, but function says cargo is too heavy";
    
    sqlite3_close(db);
}

TEST(checkCargoWeightFunctionTest, weightGreaterThanCapacity)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    
    EXPECT_EQ(checkCargoWeight(db, "1234XA", "13.5"), false) << "Weight is greater than capacity, but function says cargo is not too heavy";
    
    sqlite3_close(db);
    
}

TEST (checkGetMileageByCarFunctionTest, mileageOfCar1234XA)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    stringstream ss;
    getMileageByCar(db, "1234XA", ss);
    
    EXPECT_EQ(ss.str(), "Общий пробег:\n5270\n") << "Total mileage of car 1234XA is not correct";
    
    sqlite3_close(db);
}

TEST (checkGetMileageByCarFunctionTest, mileageOfCar1122MP)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    stringstream ss;
    getMileageByCar(db, "1122MP", ss);
    
    EXPECT_EQ(ss.str(), "Общий пробег:\n3145\n") << "Total mileage of car 1122MP is not correct";
    
    sqlite3_close(db);
}

TEST (checkGetTransportedWeightByCarFunctionTest, weightOfCar1122MP)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    stringstream ss;
    getTransportedWeightByCar(db, "1122MP", ss);
    
    EXPECT_EQ(ss.str(), "Общая масса перевезенных грузов:\n3.0\n") << "Total transported weight of car 1122MP is not correct";
    
    sqlite3_close(db);
}

TEST (checkGetTransportedWeightByCarFunctionTest, weightOfCar1234XA)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    stringstream ss;
    getTransportedWeightByCar(db, "1234XA", ss);
    
    EXPECT_EQ(ss.str(), "Общая масса перевезенных грузов:\n19.0\n") << "Total transported weight of car 1234XA is not correct";
    
    sqlite3_close(db);
}

TEST (checkNumOfTripsByDriverFunctionTest, numOfTripsOfDriver1111)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    stringstream ss;
    getNumOfTripsByDriver(db, "1111", ss);
    
    EXPECT_EQ(ss.str(), "Общее количество поездок: 3\n") << "Number of trips of driver 1111(Petrov) is not correct";
    
    sqlite3_close(db);
}

TEST (checkNumOfTripsByDriverFunctionTest, numOfTripsOfDriver1117)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    stringstream ss;
    getNumOfTripsByDriver(db, "1117", ss);
    
    EXPECT_EQ(ss.str(), "Общее количество поездок: 1\n") << "Number of trips of driver 1117(Кузнецов) is not correct";
    
    sqlite3_close(db);
}

TEST (checkGetTransportedWeightByDriverFunctionTest, transportedWeightDriver1111)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    stringstream ss;
    getTransportedWeightByDriver(db, "1111", ss);
    
    EXPECT_EQ(ss.str(), "Общая масса перевезенных грузов: 19.0\n") << "Transported weight of driver 1111(Петров) is not correct";
    
    sqlite3_close(db);
}

TEST (checkGetTransportedWeightByDriverFunctionTest, transportedWeightDriver1117)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    stringstream ss;
    getTransportedWeightByDriver(db, "1117", ss);
    
    EXPECT_EQ(ss.str(), "Общая масса перевезенных грузов: 3.0\n") << "Transported weight of driver 1117(Кузнецов) is not correct";
    
    sqlite3_close(db);
}

TEST (checkGetEarningsByDriverFunctionTest, earningsDriver1111)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    stringstream ss;
    getEarningsByDriver(db, "1111", ss);
    
    EXPECT_EQ(ss.str(), "Общая сумма заработанных денег: 1540\n") << "Earnings of driver 1111(Петров) is not correct";
    
    sqlite3_close(db);
}

TEST (checkGetEarningsByDriverFunctionTest, earningsDriver1117)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    stringstream ss;
    getEarningsByDriver(db, "1117", ss);
    
    EXPECT_EQ(ss.str(), "Общая сумма заработанных денег: 100\n") << "Earnings of driver 1117(Кузнецов) is not correct";
    
    sqlite3_close(db);
}

TEST (checkGetEarningsByDriverByPeriodFunctionTest, earningsDriver1111)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    stringstream ss;
    getEarningsByDriverByPeriod(db, "1111", "2022-04-05", "2022-04-09", ss);
    
    EXPECT_EQ(ss.str(), "Сумма заработанных денег за период с 2022-04-05 по 2022-04-09: \n1400\n") << "Earnings of driver 1111(Петров) is not correct";
    
    sqlite3_close(db);
}

TEST (checkGetEarningsByDriverByPeriodFunctionTest, earningsDriver1111Period2)
{
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    
    stringstream ss;
    getEarningsByDriverByPeriod(db, "1111", "2022-04-04", "2022-04-06", ss);
    
    EXPECT_EQ(ss.str(), "Сумма заработанных денег за период с 2022-04-04 по 2022-04-06: \n740\n") << "Earnings of driver 1111(Петров) is not correct";
    
    sqlite3_close(db);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
