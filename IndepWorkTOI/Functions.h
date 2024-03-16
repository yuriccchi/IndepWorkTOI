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

// ��������� ��������� ������ ��� �����
struct NameTreeNode
{
    string firstName;
    int index;
    NameTreeNode* left;
    NameTreeNode* right;
    NameTreeNode() : firstName(""), index(0), left(nullptr), right(nullptr) {}
    NameTreeNode(string firstName, int index) : firstName(firstName), index(index), left(nullptr), right(nullptr) {}
};

// ��������� ��������� ������ ��� ��������
struct AgeTreeNode
{
    int age;
    int index;
    AgeTreeNode* left;
    AgeTreeNode* right;
    AgeTreeNode() : age(0), index(0), left(nullptr), right(nullptr) {}
    AgeTreeNode(int age, int index) : age(age), index(index), left(nullptr), right(nullptr) {}
};

// ������� ��������� ������
struct LinkedList
{
    Data data;
    LinkedList* next;
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
int intInputMonth();
int intInputDay(int month);


//  ��� ����� 1
//// ��������
void dataInput(Data* (&d), int& n, int* (&indexes));
void printNameAscending(Data* data, int* indexes, int count);
void printAgeDescending(Data* data, int* indexes, int count);
int binarySearchByName(Data* data, int* indexes, string key, int low, int high, function<int(const Data&, string key)> comparator);
int binarySearchByAge(Data* data, int* indexes, int count, int key, function<int(const Data&, int key)> comparator);
void editRecord(Data* (&data), int count, const string& firstName, const string& lastName, const string& newFirstName, const string& newLastName, int newAge);
void deleteRecord(Data* (&data), int& count, int* (&indexes), const string& firstName);
//// ���������������
bool compareByName(const Data& a, const Data& b);
bool compareByAge(const Data& a, const Data& b);

//  ��� ����� 2
//// ��������
void insertRecord(Data*& records, AgeTreeNode*& rootByAge, NameTreeNode*& rootByFirstName, const Data& record, int& size);
void insertNodeByFirstName(NameTreeNode* node, const string& firstName, int index);
void insertNodeByAge(AgeTreeNode* node, int age, int index);
void printAscendingByFirstName(Data* records, NameTreeNode* rootByFirstName);
void printDescendingByAge(Data* records, AgeTreeNode* rootByAge);
void searchByFirstName(Data* records, NameTreeNode* rootByFirstName, const string& firstName);
void searchByAge(Data* records, AgeTreeNode* rootByAge, int age);
void editRecordbyName(Data* records, NameTreeNode* root, string firstName);
void deleteRecordByName(NameTreeNode*& root, string firstName);
//// ���������������
void printRecord(Data* records, int index);
void InorderTraversalByFirstName(Data* records, NameTreeNode* node);
void InorderTraversalByAge(Data* records, AgeTreeNode* node);
AgeTreeNode* searchNodeByAge(AgeTreeNode* node, int age);
NameTreeNode* searchNodeByFirstName(NameTreeNode* node, const string& firstName);
NameTreeNode* deleteNodeByName(NameTreeNode*& node, string firstName);
NameTreeNode* findMinName(NameTreeNode* node);
AgeTreeNode* findMinAge(AgeTreeNode* node);

//  ��� ����� 3
void insert(LinkedList*& head, Data data);
void sortByFirstName(LinkedList*& head);
void sortByAge(LinkedList*& head);
void printList(LinkedList* head);
void searchByName(LinkedList* head, string name);
void searchByAge(LinkedList* head, int age);
void deleteByName(LinkedList*& head, string name);