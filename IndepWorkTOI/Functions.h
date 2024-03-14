#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <functional>

using namespace std;

// Структура фамилии и имени
struct Initial
{
    string firstName,
        lastName;
};

// Структура даты рождения
struct Date
{
    int day,
        month;
};

// Структура возраста
struct Age
{
    int age;
};

// Структура подарка(ов)
struct Gift
{
    string loveGifts;
};

// Структура самой базы данных
struct Data
{
    Initial _initial;
    Date _date;
    Age _age;
    Gift _loveGifts;
};

// Структура для узла бинарного дерева
struct TreeNode {
    string key;
    int dataIndex;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string k, int idx) : key(k), dataIndex(idx), left(nullptr), right(nullptr) {}
};

// Компаратор для бинарного поиска по имени
static auto nameComparator = [](const Data& d, string key)
    {
        return d._initial.firstName.compare(key);
    };

// Компаратор для бинарного поиска по возрасту
static auto ageComparator = [](const Data& d, int key)
    {
        if (d._age.age == key)
            return 0;
        else if (d._age.age > key)
            return -1;
        else
            return 1;
    };

// Прототипы всех функций

int intInputValue();
int intInputDay();
int intInputMonth();

//  для части 1
void dataInput(Data* (&d), int& n, int* (&indexes));
bool compareByName(const Data& a, const Data& b);
bool compareByAge(const Data& a, const Data& b);
void printNameAscending(Data* data, int* indexes, int count);
void printAgeDescending(Data* data, int* indexes, int count);
int binarySearchByName(Data* data, int* indexes, string key, int low, int high, function<int(const Data&, string key)> comparator);
int binarySearchByAge(Data* data, int* indexes, int count, int key, function<int(const Data&, int key)> comparator);
void editRecord(Data* (&data), int count, const string& firstName, const string& lastName, const string& newFirstName, const string& newLastName, int newAge);
void deleteRecord(Data* (&data), int& count, int* (&indexes), const string& firstName);

//  для части 2

//  для части 3