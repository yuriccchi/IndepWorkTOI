#include "Functions.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

// Функция для безопасного ввода целого числа
int intInputValue()
{
    int value;
    while (!(std::cin >> value) || value < 0)
    {
        std::cout << "Ошибка ввода. Введите целое число: ";
        std::cin.clear();
        std::cin.ignore(32767, '\n');
    }
    return value;
}

// Функция для безопасного ввода дня
int intInputDay()
{
    int day;
    do
    {
        while (!(std::cin >> day) || day < 1 || day > 31)
        {
            std::cout << "Ошибка ввода. Введите номер для от 1 до 31" << std::endl;
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
    } while (day < 1 || day > 31);

    return day;
}

// Функция для безопасного ввода месяца
int intInputMonth()
{
    int month;
    do
    {
        while (!(std::cin >> month) || month < 1 || month > 12)
        {
            std::cout << "Ошибка ввода. Введите номер для от 1 до 31" << std::endl;
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
    } while (month < 1 || month > 31);

    return month;
}

// Ввод данных (Индексы)
void dataInput(Data* (&data), int& n, int* (&indexes))
{
    // Проверка на заполненность
    if (n >= 200)
    {
        cout << "Массив данных полностью заполнен. Невозможно добавить новые данные." << endl;
        return;
    }

    // Определение, сколько за раз данных ввести
    cout << "Введите количество вводимых сейчас данных: ";
    int newDataCount;
    cin >> newDataCount;

    int totalSize = n + newDataCount; // Определение нового количества данных в бд

    // Создаем временный массив для объединения старых и новых данных
    Data* newData = new Data[totalSize];

    // Копируем старые данные в новый массив
    for (int i = 0; i < n; ++i)
    {
        newData[i] = data[i];
    }

    // Добавление индексов
    for (int i = 0; i < totalSize; ++i)
    {
        indexes[i] = i;
    }

    cout << "Введите информацию" << endl;
    cout << "------------------" << endl;

    // Вводим данные
    for (int i = n; i < totalSize; ++i)
    {
        cout << "Введите имя и фамилию: ";
        cin >> newData[i]._initial.firstName >> newData[i]._initial.lastName;

        cout << "Введите день и месяц дня рождения: ";
        newData[i]._date.day = intInputDay();
        newData[i]._date.month = intInputMonth();

        cout << "Введите, сколько лет сейчас вашему другу: ";
        cin >> newData[i]._age.age;

        cout << "Введите, какие подарки любит ваш друг: ";
        cin >> newData[i]._loveGifts.loveGifts;

        cout << "___________________________" << endl;
    }

    delete[] data; // Очищаем старый массив
    data = newData; // Переключаем указатель на новый массив
    n = totalSize; // Обновляем количество элементов в массиве
}

// Сортировка по имени (возрастание)
bool compareByName(const Data& a, const Data& b)
{
    if (a._initial.firstName == b._initial.firstName)
    {
        return a._initial.lastName < b._initial.lastName;
    }
    return a._initial.firstName < b._initial.firstName;
}

// Сортировка по возрасту (убывание)
bool compareByAge(const Data& a, const Data& b)
{
    return a._age.age > b._age.age;
}

// Печать данных по возрастанию имени (по алфавиту) (Индексы)
void printNameAscending(Data* data, int* indexes, int count)
{
    if (count == 0)
    {
        cout << "Массив пуст" << endl;
        return;
    }

    sort(indexes, indexes + count, [&](int a, int b) {
        return compareByName(data[a], data[b]);
        });

    // Печать данных
    for (int i = 0; i < count; ++i)
    {
        cout << data[indexes[i]]._initial.firstName << " " << data[indexes[i]]._initial.lastName << ", возраст: " << data[indexes[i]]._age.age << " лет" << endl;
    }
}

// Печать данных по убыванию возраста (Индексы)
void printAgeDescending(Data* data, int* indexes, int count)
{
    if (count == 0)
    {
        cout << "Массив пуст" << endl;
        return;
    }

    sort(indexes, indexes + count, [&](int a, int b) {
        return compareByAge(data[a], data[b]);
        });

    // Печать данных
    for (int i = 0; i < count; ++i)
    {
        cout << data[indexes[i]]._initial.firstName << " " << data[indexes[i]]._initial.lastName << ", возраст: " << data[indexes[i]]._age.age << " лет" << endl;
    }
}

// Рекурсивный бинарный поиск по имени (Индексы)
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

// Итеративный бинарный поиск по возрасту (Индексы)
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

// Редактирование данных, выбор нужных через имя (Индексы)
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
        cout << "Запись с указанным именем и фамилией не найдена" << endl;
    }
}

// Удаление данных, выбор нужных через имя (Индексы)
void deleteRecord(Data* (&data), int& count, int* (&indexes), const string& firstName)
{
    ;
    int deletePos = binarySearchByName(data, indexes, firstName, 0, count - 1, nameComparator);

    if (deletePos == -1)
    {
        cout << "Запись с указанным именем и фамилией не найдена." << endl;
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

// 
void deleteAgeTree(AgeTreeNode* node) 
{
    if (node != nullptr)
    {
        deleteAgeTree(node->left);
        deleteAgeTree(node->right);
        delete node;
    }
}

void deleteNameTree(NameTreeNode* node) 
{
    if (node != nullptr)
    {
        deleteNameTree(node->left);
        deleteNameTree(node->right);
        delete node;
    }
}

void insertRecord(Data* &records, AgeTreeNode* &rootByAge, NameTreeNode* &rootByFirstName, const Data& record, int& size) 
{
    Data* newRecords = new Data[size + 1];
    for (int i = 0; i < size; ++i) {
        newRecords[i] = records[i];
    }
    newRecords[size++] = record;
    delete[] records;
    records = newRecords;

    int index = size - 1;

    // Добавляем в бинарное дерево по возрасту
    if (rootByAge == nullptr)
        rootByAge = new AgeTreeNode(record._age.age, index);
    else
        insertNodeByAge(rootByAge, record._age.age, index);

    // Добавляем в бинарное дерево по имени
    if (rootByFirstName == nullptr)
        rootByFirstName = new NameTreeNode(record._initial.firstName, index);
    else
        insertNodeByFirstName(rootByFirstName, record._initial.firstName, index);
}

// Вспомогательная функция для сортировки по возрасту
void insertNodeByAge(AgeTreeNode* node, int age, int index) 
{
    if (age < node->age)
    {
        if (node->left == nullptr)
        {
            node->left = new AgeTreeNode(age, index);
        }
        else
        {
            insertNodeByAge(node->left, age, index);
        }
    }
    else 
    {
        if (node->right == nullptr)
        {
            node->right = new AgeTreeNode(age, index);
        }
        else
        {
            insertNodeByAge(node->right, age, index);
        }
    }
}

// Вспомогательная функция для сортировки по имени
void insertNodeByFirstName(NameTreeNode* node, const string& firstName, int index) 
{
    if (firstName < node->firstName) {
        if (node->left == nullptr) {
            node->left = new NameTreeNode(firstName, index);
        }
        else {
            insertNodeByFirstName(node->left, firstName, index);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new NameTreeNode(firstName, index);
        }
        else {
            insertNodeByFirstName(node->right, firstName, index);
        }
    }
}

// Печать по убыванию возраста (Бинарное дерево)
void printDescendingByAge(Data* records, AgeTreeNode* rootByAge)
{
    inorderTraversalByAge(records, rootByAge);
}

// Вспомогательная функция для печати по возрасту
void inorderTraversalByAge(Data* records, AgeTreeNode* node) {
    if (node != nullptr) {
        inorderTraversalByAge(records, node->left);
        printRecord(records, node->index);
        inorderTraversalByAge(records, node->right);
    }
}

// Печать по возрастанию имени (по алфавиту) (Бинарное дерево)
void printAscendingByFirstName(Data* records, NameTreeNode* rootByFirstName)
{
    inorderTraversalByFirstName(records, rootByFirstName);
}

// Вспомогательная функция для печати по имени
void inorderTraversalByFirstName(Data* records, NameTreeNode* node) {
    if (node != nullptr) {
        inorderTraversalByFirstName(records, node->left);
        printRecord(records, node->index);
        inorderTraversalByFirstName(records, node->right);
    }
}

// Функция печати данных
void printRecord(Data* records, int index)
{
    Data record = records[index];
    cout << record._initial.firstName << record._initial.lastName << ", возраст: " << record._age.age << ", любимые подарки: " << record._loveGifts.loveGifts << endl;
    cout << endl;
}

// Поиск по возрасту
void searchByAge(Data* records, AgeTreeNode* rootByAge, int age)
{
    AgeTreeNode* result = searchNodeByAge(rootByAge, age);
    if (result != nullptr)
        printRecord(records, result->index);
    else
        cout << "Данные не найлены" << endl;
}

// Поиск по имени
void searchByFirstName(Data* records, NameTreeNode* rootByFirstName, const string& firstName)
{
    NameTreeNode* result = searchNodeByFirstName(rootByFirstName, firstName);
    if (result != nullptr)
        printRecord(records, result->index);
    else
        cout << "Данные не найлены" << endl;
}

// Вспомогательная функция для поиска по возрасту
AgeTreeNode* searchNodeByAge(AgeTreeNode* node, int age)
{
    if (node == nullptr || node->age == age)
        return node;

    if (age < node->age)
        return searchNodeByAge(node->left, age);
    else
        return searchNodeByAge(node->right, age);
}

// Вспомогательная функция для поиска по имени
NameTreeNode* searchNodeByFirstName(NameTreeNode* node, const string& firstName)
{
    if (node == nullptr || node->firstName == firstName)
        return node;

    if (firstName < node->firstName)
        return searchNodeByFirstName(node->left, firstName);
    else
        return searchNodeByFirstName(node->right, firstName);
}

//Редактирование записи по возрасту
void editRecordbyAge(Data* records, AgeTreeNode* root, int age, const Data& newData)
{
    AgeTreeNode* result = searchNodeByAge(root, age);
    if (result != nullptr)
    {
        records[result->index] = newData;
        result->age = newData._age.age;
    }
    else
    {
        cout << "Данные не найдены" << endl;
    }
}

// Редактирование записи по имени
void editRecordbyName(Data* records, NameTreeNode* root, string firstName, const Data& newData)
{
    NameTreeNode* result = searchNodeByFirstName(root, firstName);
    if (result != nullptr)
    {
        records[result->index] = newData;
        result->firstName = newData._initial.firstName;
    }
    else
    {
        cout << "Данные не найдены" << endl;
    }
}

// Функция удаления
void deleteRecordByAge(AgeTreeNode* &root, int age)
{
    deleteNodeByAge(root, age);
}

// Сам алгоритм выполнения удаления по возрасту
AgeTreeNode* deleteNodeByAge(AgeTreeNode*& node, int age)
{
    if (node == nullptr)
        return node;

    if (age < node->age)
        node->left = deleteNodeByAge(node->left, age);
    else if (age > node->age)
        node->right = deleteNodeByAge(node->right, age);
    else
    {
        if (node->left == nullptr)
        {
            AgeTreeNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            AgeTreeNode* temp = node->left;
            delete node;
            return temp;
        }

        AgeTreeNode* minRight = findMinAge(node->right);
        node->age = minRight->age;
        node->index = minRight->index;
        node->right = deleteNodeByAge(node->right, minRight->age);
    }

    return node;
}

AgeTreeNode* findMinAge(AgeTreeNode* node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

void deleteRecordByName(NameTreeNode*& root, string firstName)
{
    deleteNodeByName(root, firstName);
}

NameTreeNode* deleteNodeByName(NameTreeNode*& node, string firstName)
{
    if (node == nullptr)
        return node;

    if (firstName < node->firstName)
        node->left = deleteNodeByName(node->left, firstName);
    else if (firstName > node->firstName) {
        node->right = deleteNodeByName(node->right, firstName);
    }
    else 
    {
        if (node->left == nullptr)
        {
            NameTreeNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            NameTreeNode* temp = node->left;
            delete node;
            return temp;
        }

        NameTreeNode* minRight = findMinName(node->right);
        node->firstName = minRight->firstName;
        node->index = minRight->index;
        node->right = deleteNodeByName(node->right, minRight->firstName);
    }

    return node;
}

NameTreeNode* findMinName(NameTreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}