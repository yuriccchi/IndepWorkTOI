#include "Functions.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

// ������� ��� ����������� ����� ������ �����
int intInputValue()
{
    int value;
    while (!(std::cin >> value) || value < 0)
    {
        std::cout << "������ �����. ������� ����� �����: ";
        std::cin.clear();
        std::cin.ignore(32767, '\n');
    }
    return value;
}

// ������� ��� ����������� ����� ���
int intInputDay()
{
    int day;
    do
    {
        while (!(std::cin >> day) || day < 1 || day > 31)
        {
            std::cout << "������ �����. ������� ����� ��� �� 1 �� 31" << std::endl;
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
    } while (day < 1 || day > 31);

    return day;
}

// ������� ��� ����������� ����� ������
int intInputMonth()
{
    int month;
    do
    {
        while (!(std::cin >> month) || month < 1 || month > 12)
        {
            std::cout << "������ �����. ������� ����� ��� �� 1 �� 31" << std::endl;
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
    } while (month < 1 || month > 31);

    return month;
}

// ���������� �� ����� (�����������)
bool compareByName(const Data& a, const Data& b)
{
    if (a._initial.firstName == b._initial.firstName)
    {
        return a._initial.lastName < b._initial.lastName;
    }
    return a._initial.firstName < b._initial.firstName;
}

// ���������� �� �������� (��������)
bool compareByAge(const Data& a, const Data& b)
{
    return a._age.age > b._age.age;
}

// ���� ������
void dataInput(Data* (&data), int& n, int* (&indexes))
{
    // �������� �� �������������
    if (n >= 200)
    {
        cout << "������ ������ ��������� ��������. ���������� �������� ����� ������." << endl;
        return;
    }

    // �����������, ������� �� ��� ������ ������
    cout << "������� ���������� �������� ������ ������: ";
    int newDataCount;
    cin >> newDataCount;

    int totalSize = n + newDataCount; // ����������� ������ ���������� ������ � ��

    // ������� ��������� ������ ��� ����������� ������ � ����� ������
    Data* newData = new Data[totalSize];

    // �������� ������ ������ � ����� ������
    for (int i = 0; i < n; ++i)
    {
        newData[i] = data[i];
    }

    // ���������� ��������
    for (int i = 0; i < totalSize; ++i)
    {
        indexes[i] = i;
    }

    cout << "������� ����������" << endl;
    cout << "------------------" << endl;

    // ������ ������
    for (int i = n; i < totalSize; ++i)
    {
        cout << "������� ��� � �������: ";
        cin >> newData[i]._initial.firstName >> newData[i]._initial.lastName;

        cout << "������� ���� � ����� ��� ��������: ";
        newData[i]._date.day = intInputDay();
        newData[i]._date.month = intInputMonth();

        cout << "�������, ������� ��� ������ ������ �����: ";
        cin >> newData[i]._age.age;

        cout << "�������, ����� ������� ����� ��� ����: ";
        cin >> newData[i]._loveGifts.loveGifts;

        cout << "___________________________" << endl;
    }

    delete[] data; // ������� ������ ������
    data = newData; // ����������� ��������� �� ����� ������
    n = totalSize; // ��������� ���������� ��������� � �������
}

// ������ ������ �� ����������� ����� (�� ��������)
void printNameAscending(Data* data, int* indexes, int count)
{
    if (count == 0)
    {
        cout << "������ ����" << endl;
        return;
    }

    sort(indexes, indexes + count, [&](int a, int b) {
        return compareByName(data[a], data[b]);
        });

    // ������ ������
    for (int i = 0; i < count; ++i)
    {
        cout << data[indexes[i]]._initial.firstName << " " << data[indexes[i]]._initial.lastName << ", �������: " << data[indexes[i]]._age.age << " ���" << endl;
    }
}

// ������ ������ �� �������� ��������
void printAgeDescending(Data* data, int* indexes, int count)
{
    if (count == 0)
    {
        cout << "������ ����" << endl;
        return;
    }

    sort(indexes, indexes + count, [&](int a, int b) {
        return compareByAge(data[a], data[b]);
        });

    // ������ ������
    for (int i = count - 1; i >= 0; --i)
    {
        cout << data[indexes[i]]._initial.firstName << " " << data[indexes[i]]._initial.lastName << ", �������: " << data[indexes[i]]._age.age << " ���" << endl;
    }
}

// ����������� �������� ����� �� �����
int binarySearchByName(Data* data, int* indexes, string key, int low, int high, function<int(const Data&, string key)> comparator)
{
    if (low > high)
        return -1;

    int mid = low + (high - low) / 2;

    if (comparator(data[indexes[mid]], key) == 0)
        return mid;
    else if (comparator(data[indexes[mid]], key) < 0)
        return binarySearchByName(data, indexes, key, mid + 1, high, comparator);
    else
        return binarySearchByName(data, indexes, key, low, mid - 1, comparator);
}

// ����������� �������� ����� �� ��������
int binarySearchByAge(Data* data, int* indexes, int count, int key, function<int(const Data&, int key)> comparator)
{
    int low = 0;
    int high = count - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (comparator(data[indexes[mid]], key) == 0)
        {
            return mid;
        }
        else if (comparator(data[indexes[mid]], key) < 0)
        {
            return mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

// �������������� ������, ����� ������ ����� ���-�������
void editRecord(Data* (&data), int count, const string& firstName, const string& lastName, const string& newFirstName, const string& newLastName, int newAge)
{
    bool found = false;
    for (int i = 0; i < count; ++i)
    {
        if (data[i]._initial.firstName == firstName && data[i]._initial.lastName == lastName)
        {
            data[i]._initial.firstName = newFirstName;
            data[i]._initial.lastName = newLastName;
            data[i]._age.age = newAge;

            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "������ � ��������� ������ � �������� �� �������" << endl;
    }
}

// �������� ������, ����� ������ ����� ���-�������
void deleteRecord(Data* (&data), int& count, int* (&indexes), const string& firstName)
{
    ;
    int deletePos = binarySearchByName(data, indexes, firstName, 0, count - 1, nameComparator);

    if (deletePos == -1)
    {
        cout << "������ � ��������� ������ � �������� �� �������." << endl;
    }
    else
    {
        int newSize = count - 1;

        if (newSize <= 0)
        {
            data = new Data[0];
            indexes = new int[0];
            count = 0;

            return;
        }

        Data* newBooks = new Data[newSize];
        int* newIndexes = new int[newSize];

        int i;
        for (i = 0; indexes[i] != deletePos; i++)
        {
            if (indexes[i] < deletePos)
                newIndexes[i] = indexes[i];
            else
                newIndexes[i] = indexes[i] - 1;
        }
        for (i; i < newSize; i++)
        {
            if (indexes[i] < deletePos)
                newIndexes[i] = indexes[i + 1];
            else
                newIndexes[i] = indexes[i + 1] - 1;
        }
        for (i = 0; i < newSize; i++)
        {
            if (i < deletePos)
                newBooks[i] = data[i];
            else
                newBooks[i] = data[i + 1];
        }

        data = newBooks;
        indexes = newIndexes;
        count = newSize;
    }
}