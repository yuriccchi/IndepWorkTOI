#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <functional>

using namespace std;

// ��������� ������� � �����
struct Initial
{
    string firstName,
        lastName;
};

// ��������� ���� ��������
struct Date
{
    int day,
        month;
};

// ��������� ��������
struct Age
{
    int age;
};

// ��������� �������(��)
struct Gift
{
    string loveGifts;
};

// ��������� ����� ���� ������
struct Data
{
    Initial _initial;
    Date _date;
    Age _age;
    Gift _loveGifts;
};

// ��������� ��� ���� ��������� ������
struct TreeNode {
    string key;
    int dataIndex;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string k, int idx) : key(k), dataIndex(idx), left(nullptr), right(nullptr) {}
};

// ���������� ��� ��������� ������ �� �����
static auto nameComparator = [](const Data& d, string key)
    {
        return d._initial.firstName.compare(key);
    };

// ���������� ��� ��������� ������ �� ��������
static auto ageComparator = [](const Data& d, int key)
    {
        if (d._age.age == key)
            return 0;
        else if (d._age.age > key)
            return -1;
        else
            return 1;
    };

// ��������� ���� �������

int intInputValue();
int intInputDay();
int intInputMonth();

//  ��� ����� 1
void dataInput(Data* (&d), int& n, int* (&indexes));
bool compareByName(const Data& a, const Data& b);
bool compareByAge(const Data& a, const Data& b);
void printNameAscending(Data* data, int* indexes, int count);
void printAgeDescending(Data* data, int* indexes, int count);
int binarySearchByName(Data* data, int* indexes, string key, int low, int high, function<int(const Data&, string key)> comparator);
int binarySearchByAge(Data* data, int* indexes, int count, int key, function<int(const Data&, int key)> comparator);
void editRecord(Data* (&data), int count, const string& firstName, const string& lastName, const string& newFirstName, const string& newLastName, int newAge);
void deleteRecord(Data* (&data), int& count, int* (&indexes), const string& firstName);

//  ��� ����� 2

//  ��� ����� 3