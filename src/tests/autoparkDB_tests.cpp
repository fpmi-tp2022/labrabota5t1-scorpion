#include <iostream>
#include <gtest/gtest.h>
#include <sqlite3.h>

using namespace std;

bool checkCargoWeight(sqlite3* , string, string);

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
    
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
