#include <iostream>
#include <gtest/gtest.h>
#include <sqlite3.h>

using namespace std;

string getDriverServiceNumber(istream&);
string getCarNumber(istream&);
string getPeriodData(istream&);

TEST(testGetDriverServiceNumber, input1111)
{
    stringstream in;
    in << "1111";
    
    EXPECT_EQ(getDriverServiceNumber(in), "1111") << "Driver number is not correct";
}

TEST(testGetDriverServiceNumber, input2345)
{
    stringstream in;
    in << "2345";
    
    EXPECT_EQ(getDriverServiceNumber(in), "2345") << "Driver number is not correct";
}

TEST(testCarNumber, input1122PQ)
{
    stringstream in;
    in << "1122PQ";
    
    EXPECT_EQ(getCarNumber(in), "1122PQ") << "Car number is not correct";
}


TEST(testCarNumber, input7891MN)
{
    stringstream in;
    in << "7891MN";
    
    EXPECT_EQ(getCarNumber(in), "7891MN") << "Car number is not correct";
}

TEST(testGetPeriodDataFunction, test1)
{
    stringstream in;
    in << "нет\n2022-04-05\n2022-04-08";
    EXPECT_EQ(getPeriodData(in), "'2022-04-05' and '2022-04-08'") << "Period is not correct";
    
}
 
TEST(testGetPeriodDataFunction, test2)
{
    stringstream in;
    in << "да";
    EXPECT_EQ(getPeriodData(in), "all") << "Expected 'all' for all period";
    
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
