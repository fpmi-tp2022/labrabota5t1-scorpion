// main.cpp
// lab5

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <fstream>
#include "../include/autoparkDB.h"
#include "../include/autoparkUI.h"
using namespace std;

bool checkLogin(string login, string password)
{
    ifstream fin("passwords.txt");
    if(!fin.is_open())
    {
        cerr << "Can't check password";
        exit(0);
    }
    
    bool loginIsCorrect = false;
    bool passwordIsCorrect = false;
    
    string line;
    int spaceIdx = 0;
    while (getline(fin, line))
    {
        spaceIdx = line.find(' ');
        if(line.substr(0, spaceIdx) == login)
        {
            loginIsCorrect = true;
            if(line.substr(spaceIdx+1, line.length() - spaceIdx-1) == password)
            {
                passwordIsCorrect = true;
            }
            break;
        }
    }
    
    if(!loginIsCorrect)
    {
        cout << "Пользователя с таким именем не существует\n";
        return false;
    }
    if(!passwordIsCorrect)
    {
        cout << "Неверный пароль\n";
        return false;
    }
    return true;
}



string authorize()
{
    cout << "Вход в систему\n";
    
    string userName;
    string password;
    
    bool enteredSystem = false;
    while(!enteredSystem)
    {
        cout << "Введите имя пользователя:\n";
        
        getline(cin, userName);
        cout << "Введите пароль:\n";
        
        getline(cin, password);
           
        if(!checkLogin(userName, password))
        {
            continue;
        }
        break;
    }
    return userName;
}

bool getDriversNumber(sqlite3 *db, string login, string& driversServiceNumber)
{
    string sql = "SELECT drivers_service_number FROM users WHERE login='" + login + "'";
    
    sqlite3_stmt *res;
    
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
    
    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    
    int step = sqlite3_step(res);
    
    string driversNumberStr;
    if (step == SQLITE_ROW)
    {
        driversNumberStr = (char*)sqlite3_column_text(res, 0);
    }
    
    sqlite3_finalize(res);
    
    if(driversNumberStr == "")
    {
        driversServiceNumber = "";
        return false;
    }
    else
    {
        driversServiceNumber = driversNumberStr;
        return true;
    }
}

int main()
{
    
    sqlite3 *db;
    int rc = sqlite3_open("autopark.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return -1;
    }
    
    string login = authorize();
    string driversServiceNumber;
    bool isAdmin = false;
    
    if(!getDriversNumber(db, login, driversServiceNumber))
    {
        isAdmin = true;
    }
    
    if(isAdmin)
    {
        bool continueBool = true;
        
        while(continueBool)
        {
            int option = 0;
            printAdminMenu();
            cin >> option;
            
            switch(option)
            {
                case 1:
                {
                    string table = "";
                    string insertStr = "";
                    string driverServiceNumber = "";
                    string photoFileName = "";
                    insertStr = getIndertData(table, photoFileName, driverServiceNumber);
                    string photoFileNameWithPath = "./img//" + photoFileName;
                    insert(db, table, insertStr, photoFileNameWithPath, driverServiceNumber);
                    break;
                }
                case 2:
                {
                    string table = "";
                    string column = "";
                    string value = "";
                    string columnToChange = "";
                    string newValue = getUpdateValue(table, column, value, columnToChange);
                    update(db, table, column, value, columnToChange, newValue);
                    break;
                }
                case 3:
                {
                    string table = "";
                    string column = "";
                    string deleteValue = getDeleteData(table, column);
                    deleteRecord(db, table, column, deleteValue);
                    break;
                }
                case 4:
                {
                    cout << "1. Вывести всю таблицу" << endl;
                    cout << "2. По указанному водителю вывести перечень выполненных заказов за указанный период" << endl;
                    cout << "3. По указанной машине вывести общий пробег и общую массу перевезенных грузов" << endl;
                    cout << "4. По каждому водителю вывести общее количество поездок, общую массу перевезенных грузов и сумму заработанных денег" << endl;
                    cout << "5. По водителю, выполнившему наименьшее количество поездок, вывести все сведения и количество полученных денег" << endl;
                    cout << "6. По автомашине с наибольшим общим пробегом вывести все сведения" << endl;
                    cout << "7. По указанному водителю вывести заработок за период\n";
                    
                    int choice = 0;
                    cin >> choice;
                    
                    switch(choice)
                    {
                        case 1:
                        {
                            int columnNumber = 0;
                            string columnNames = "";
                            string table = getSelectData(columnNumber, columnNames);
                            cout << columnNames << endl;
                            selectAllRecords(db, table, columnNumber);
                            break;
                        }
                        case 2:
                        {
                            string driverServiceNumber = getDriverServiceNumber();
                            string period = getPeriodData();
                            string columnNames = "|id|date|driver_last_name|car_number|kilometrage|cargo_weight|cost|driver_service_number|";
                            cout << columnNames << endl;
                            getOrdersByDriver(db, driverServiceNumber, period);
                            break;
                        }
                        case 3:
                        {
                            string carNumber = getCarNumber();
                            getMileageByCar(db, carNumber);
                            getTransportedWeightByCar(db, carNumber);
                            break;
                        }
                        case 4:
                        {
                            getNumOfTripsTransportedWeightEarningsOfAllDrivers(db);
                            break;
                        }
                        case 5:
                        {
                            getDriverWithMinTripsNumInfo(db);
                            break;
                        }
                        case 6:
                        {
                            getCarWithMaxMileage(db);
                            break;
                        }
                        case 7:
                        {
                            string driverNumber;
                            cout << "Введите табельный номер водителя: ";
                            getline(cin, driverNumber);
                            getline(cin, driverNumber);
                            string startDate;
                            cout << "Введите дату начала периода: ";
                            getline(cin, startDate);
                            string endDate;
                            cout << "Введите дату окончания периода: ";
                            getline(cin, endDate);
                            getEarningsByDriverByPeriod(db, driverNumber, startDate, endDate);
                            break;
                        }
                        default:
                        {
                            cout << "Выбранной опции не существует" << endl;
                            break;
                        }
                    }
                    break;
                }
                case 5:
                {
                    continueBool = false;
                    break;
                }
                default:
                {
                    cout << "Выбранной опции не существует" << endl;
                    break;
                }
            }
            
        }
    }
    else
    {
        bool continueBool = true;
        while(continueBool)
        {
            char option;
            printDriverMenu();
            cin >> option;
            
            switch(option)
            {
                case '1':
                {
                    string period = getPeriodData();
                    string columnNames = "|id|date|driver_last_name|car_number|kilometrage|cargo_weight|cost|driver_service_number|";
                    cout << columnNames << endl;
                    getOrdersByDriver(db, driversServiceNumber, period);
                    break;
                }
                case '2':
                    getNumOfTripsByDriver(db, driversServiceNumber);
                    break;
                case '3':
                    getTransportedWeightByDriver(db, driversServiceNumber);
                    break;
                case '4':
                {
                    getEarningsByDriver(db, driversServiceNumber);
                    break;
                }
                case '5':
                {
                    string startDate;
                    cout << "Введите дату начала периода: ";
                    getline(cin, startDate);
                    getline(cin, startDate);
                    string endDate;
                    cout << "Введите дату окончания периода: ";
                    getline(cin, endDate);
                    getEarningsByDriverByPeriod(db, driversServiceNumber, startDate, endDate);
                    break;
                }
                case '6':
                    getCarWithMaxMileage(db);
                    break;
                case '7':
                    continueBool = false;
                    break;
                default:
                    cout << "Выбранной опции не существует" << endl;
                    break;
            }
        }
       
        
    }
    
    sqlite3_close(db);
    return 0;
}

