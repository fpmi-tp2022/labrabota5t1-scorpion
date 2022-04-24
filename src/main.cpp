// main.cpp
// lab5

#include <iostream>
#include <sqlite3.h>
#include <string>
#include "../include/autoparkDB.h"
#include "../include/autoparkUI.h"
using namespace std;

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
                insertStr = getIndertData(table);
                insert(db, table, insertStr);
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
                
                int choice = 0;
                cin >> choice;
                
                switch(choice)
                {
                    case 1:
                    {
                        int count = 0;
                        string table = getSelectData(count);
                        selectAllRecords(db, table, count);
                        break;
                    }
                    case 2:
                    {
                        string driverServiceNumber = getDriverData();
                        string period = getPeriodData();
                        getOrdersByDriver(db, driverServiceNumber, period);
                        break;
                    }
                    case 3:
                    {
                        string carNumber = getCarData();
                        getMileageByCar(db, carNumber);
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
                continueBool = false;
                break;
            default:
                cout << "Выбранной опции не существует" << endl;
                break;
        }
        
    }
    
    sqlite3_close(db);
    return 0;
}
