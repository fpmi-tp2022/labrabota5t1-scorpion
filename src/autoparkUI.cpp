// autoparkUI.cpp
// lab5

#include <iostream>
#include <stdio.h>
#include <string>
#include "../include/autoparkUI.h"
using namespace std;

// Get data for inserting into a table
string getIndertData(string& table)
{
    string data = "";
    
    cout << "1. Вставить данные в таблицу users" << endl;
    cout << "2. Вставить данные в таблицу drivers" << endl;
    cout << "3. Вставить данные в таблицу cars" << endl;
    cout << "4. Вставить данные в таблицу completed_orders" << endl;
    
    int option = 0;
    cin >> option;
    
    switch (option)
    {
        case 1:
        {
            table = "users";
            string login;
            string driverServiceNumber;
            cout << "Введите логин" << endl;
            cin >> login;
            cout << "Введите табельный номер водителя" << endl;
            cin >> driverServiceNumber;
            data = "'" + login + "', '" + driverServiceNumber + "'";
            break;
        }
        case 2:
        {
            table = "drivers";
            string serviceNumber;
            string lastName;
            string category;
            string workExperience;
            string address;
            string birthYear;
            string carNumber;
            string photoFileName = "Нет фото";
            cout << "Введите табельный номер водителя" << endl;
            cin >> serviceNumber;
            cout << "Введите фамилию водителя" << endl;
            cin >> lastName;
            cout << "Введите категорию водителя" << endl;
            cin >> category;
            cout << "Введите опыт работы водителя" << endl;
            cin >> workExperience;
            cout << "Введите адрес проживания водителя" << endl;
            cin >> address;
            cout << "Введите год рождения водителя" << endl;
            cin >> birthYear;
            cout << "Введите номер машины водителя" << endl;
            cin >> carNumber;
            /*cout << "Введите название файла с фотографией водителя" << endl;
            cin >> photoFileName;*/            
            
            data = "'" + serviceNumber + "', '" + lastName + "', '" + category + "', '" + workExperience + "', '" + address + "', '" + birthYear + "', '" + carNumber + "', '" + photoFileName + "'";
            break;
        }
        case 3:
        {
            table = "cars";
            string carNumber;
            string brand;
            string mileage;
            string capacity;
            cout << "Введите номер машины" << endl;
            cin >> carNumber;
            cout << "Введите марку машины" << endl;
            cin >> brand;
            cout << "Введите пробег машины на момент приобретения" << endl;
            cin >> mileage;
            cout << "Введите грузоподъемность" << endl;
            cin >> capacity;
            data = "'" + carNumber + "', '" + brand + "', '" + mileage + "', '" + capacity + "'";
            break;
        }
        case 4:
        {
            table = "completed_orders";
            string id;
            string date;
            string driverLastName;
            string carNumber;
            string kilometrage;
            string cargoWeight;
            string cost;
            string driverServiceNumber;
            cout << "Введите номер заказа" << endl;
            cin >> id;
            cout << "Введите дату заказа" << endl;
            cin >> date;
            cout << "Введите фамилию водителя, выполнившего заказ" << endl;
            cin >> driverLastName;
            cout << "Введите номер машины" << endl;
            cin >> carNumber;
            cout << "Введите километраж" << endl;
            cin >> kilometrage;
            cout << "Введите массу груза" << endl;
            cin >> cargoWeight;
            cout << "Введите стоимость перевозки" << endl;
            cin >> cost;
            cout << "Введите табельный номер водителя" << endl;
            cin >> driverServiceNumber;
            data = "'" + id + "', '" + date + "', '" + driverLastName + "', '" + carNumber + "', '" + kilometrage + "', '" + cargoWeight + "', '" + cost + "', '" + driverServiceNumber + "'";
            break;
        }
        default:
        {
            cout << "Выбранной опции не существует" << endl;
            break;
        }
    }
    
    return data;
}

// Get data for deleting record from table
string getDeleteData(string& table, string& column)
{
    string data = "";
    
    cout << "1. Удалить данные из таблицы users" << endl;
    cout << "2. Удалить данные из таблицы drivers" << endl;
    cout << "3. Удалить данные из таблицы cars" << endl;
    cout << "4. Удалить данные из таблицы completed_orders" << endl;
    
    int option = 0;
    cin >> option;
    
    switch(option)
    {
        case 1:
        {
            table = "users";
            column = "login";
            cout << "Введите логин пользователя" << endl;
            cin >> data;
            break;
        }
        case 2:
        {
            table = "drivers";
            column = "service_number";
            cout << "Введите табельный номер водителя" << endl;
            cin >> data;
            break;
        }
        case 3:
        {
            table = "cars";
            column = "car_number";
            cout << "Введите номер машины" << endl;
            cin >> data;
            break;
        }
        case 4:
        {
            table = "completed_orders";
            column = "id";
            cout << "Введите номер заказа" << endl;
            cin >> data;
            break;
        }
        default:
        {
            cout << "Выбранной опции не существует" << endl;
            break;
        }
    }
    
    return data;
}

// Get data for updating record in table
string getUpdateValue(string& table, string& column, string& value, string& columnToChange)
{
    string data = "";
    
    cout << "1. Обновить все данные в таблице users" << endl;
    cout << "2. Обновить все данные в таблице drivers" << endl;
    cout << "3. Обновить все данные в таблице cars" << endl;
    cout << "4. Обновить все данные в таблице completed_orders" << endl;
    
    int option = 0;
    cin >> option;
    
    switch(option)
    {
        case 1:
        {
            table = "users";
            column = "login";
            cout << "Введите логин пользователя" << endl;
            cin >> value;
            cout << "Введите название колонки, в которой хотите изменить значение" << endl;
            cin >> columnToChange;
            cout << "Введите новое значение" << endl;
            cin >> data;
            break;
        }
        case 2:
        {
            table = "drivers";
            column = "service_number";
            cout << "Введите табельный номер водителя" << endl;
            cin >> value;
            cout << "Введите название колонки, в которой хотите изменить значение" << endl;
            cin >> columnToChange;
            cout << "Введите новое значение" << endl;
            cin >> data;
            break;
        }
        case 3:
        {
            table = "cars";
            column = "car_number";
            cout << "Введите номер машины" << endl;
            cin >> value;
            cout << "Введите название колонки, в которой хотите изменить значение" << endl;
            cin >> columnToChange;
            cout << "Введите новое значение" << endl;
            cin >> data;
            break;
        }
        case 4:
        {
            table = "completed_orders";
            column = "id";
            cout << "Введите номер заказа" << endl;
            cin >> value;
            cout << "Введите название колонки, в которой хотите изменить значение" << endl;
            cin >> columnToChange;
            cout << "Введите новое значение" << endl;
            cin >> data;
            break;
        }
        default:
        {
            cout << "Выбранной опции не существует" << endl;
            break;
        }
    }
    
    return data;
}

// Get all data from a table
string getSelectData(int &count)
{
    string data = "";
    
    cout << "1. Вывести все данные из таблицы users" << endl;
    cout << "2. Вывести все данные из таблицы drivers" << endl;
    cout << "3. Вывести все данные из таблицы cars" << endl;
    cout << "4. Вывести все данные из таблицы completed_orders" << endl;
    
    int option = 0;
    cin >> option;
    
    switch(option)
    {
        case 1:
        {
            data = "users";
            count = 2;
            break;
        }
        case 2:
        {
            data = "drivers";
            count = 8;
            break;
        }
        case 3:
        {
            data = "cars";
            count = 4;
            break;
        }
        case 4:
        {
            data = "completed_orders";
            count = 8;
            break;
        }
        default:
        {
            cout << "Выбранной опции не существует" << endl;
            break;
        }
    }
    
    return data;
}

// Print menu for admin
void printAdminMenu()
{
    cout << "Меню:" << endl;
    cout << "1. Вставить данные" << endl;
    cout << "2. Обновить данные" << endl;
    cout << "3. Удалить данные" << endl;
    cout << "4. Выбрать данные" << endl;
    cout << "5. Выйти" << endl;
}