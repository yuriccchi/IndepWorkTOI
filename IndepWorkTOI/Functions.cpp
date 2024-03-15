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

// Редактирование данных, выбор нужных через имя-фамилия (Индексы)
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

// Удаление данных, выбор нужных через имя-фамилия (Индексы)
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

// Функция вставки нового узла в дерево (Бинарное дерево)
Data* insert(Data* node, const Data& data) {
    if (node == nullptr) {
        return createNode(data);  // Создание нового узла
    }

    // Рекурсивное вставка узла в соответствующее поддерево
    if (data._initial.firstName < node->_initial.firstName) {
        node->left = insert(node->left, data);  // Вставка в левое поддерево
    }
    else if (data._initial.firstName > node->_initial.firstName) {
        node->right = insert(node->right, data);  // Вставка в правое поддерево
    }
    else {
        // Обработка дубликатов, если они не поддерживаются
        return node;
    }

    // Обновление высоты узла
    node->height = 1 + max(height(node->left), height(node->right));

    // Вычисление коэффициента балансировки для узла
    int balance = balanceFactor(node);

    // Балансировка дерева
    if (balance > 1 && data._initial.firstName < node->left->_initial.firstName)
        return rotateRight(node);  // Левый левый случай

    if (balance > 1 && data._initial.firstName > node->left->_initial.firstName) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);  // Левый правый случай
    }

    if (balance < -1 && data._initial.firstName > node->right->_initial.firstName)
        return rotateLeft(node);  // Правый правый случай

    if (balance < -1 && data._initial.firstName < node->right->_initial.firstName) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);  // Правый левый случай
    }

    return node;
}

// Функция поиска по имени (Бинарное дерево)
void searchByName(Data* root, const string& firstName) {
    searchByNameUtil(root, firstName);
}

// Функция поиска по возрасту (Бинарное дерево)
void searchByAge(Data* root, int age) {
    searchByAgeUtil(root, age);
}

// Функция удаления узла из дерева по имени (Бинарное дерево)
Data* remove(Data* root, const string& firstName) {
    return removeUtil(root, firstName);
}

// Вспомогательная функция для получения высоты узла (Бинарное дерево)
int height(Data* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Вспомогательная функция для вычисления коэффициента балансировки узла (Бинарное дерево)
int balanceFactor(Data* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

// Вспомогательная функция для выполнения правого вращения узла (Бинарное дерево)
Data* rotateRight(Data* y) {
    Data* x = y->left;
    Data* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Вспомогательная функция для выполнения левого вращения узла (Бинарное дерево)
Data* rotateLeft(Data* x) {
    Data* y = x->right;
    Data* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Вспомогательная функция для создания нового узла (Бинарное дерево)
Data* createNode(const Data& data)
{
    Data* newNode = new Data();
    newNode->_initial = data._initial;
    /*newNode->_date = data._date;*/
    newNode->_age = data._age;
    /*newNode->_loveGifts = data._loveGifts;*/
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}

// Вспомогательная функция для поиска по имени в дереве (Бинарное дерево)
void searchByNameUtil(Data* node, const string& firstName) 
{
    if (node == nullptr) return;

    if (node->_initial.firstName == firstName)
    {
        // Вывод или дальнейшая обработка найденных данных
        cout << "Name: " << node->_initial.firstName << " " << node->_initial.lastName << endl;
        /*cout << "Date of Birth: " << node->_date.day << "/" << node->_date.month << endl;*/
        cout << "Age: " << node->_age.age << endl;
        /*cout << "Gifts: " << node->_loveGifts.loveGifts << endl;*/

        return;
    }

    if (firstName < node->_initial.firstName)
    {
        searchByNameUtil(node->left, firstName);
    }
    else
    {
        searchByNameUtil(node->right, firstName);
    }
}

// Вспомогательная функция для поиска по возрасту в дереве (Бинарное дерево)
void searchByAgeUtil(Data* node, int age) 
{
    if (node == nullptr) return;

    if (node->_age.age == age)
    {
        // Вывод или дальнейшая обработка найденных данных
        cout << "Name: " << node->_initial.firstName << " " << node->_initial.lastName << endl;
        /*cout << "Date of Birth: " << node->_date.day << "/" << node->_date.month << endl;*/
        cout << "Age: " << node->_age.age << endl;
        /*cout << "Gifts: " << node->_loveGifts.loveGifts << endl;*/

        return;
    }

    if (age < node->_age.age)
    {
        searchByAgeUtil(node->left, age);
    }
    else
    {
        searchByAgeUtil(node->right, age);
    }
}

// Вспомогательная функция для поиска минимального узла в правом поддереве (Бинарное дерево)
Data* minValueNode(Data* node)
{
    Data* current = node;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

// Вспомогательная функция для удаления узла из дерева (Бинарное дерево)
Data* removeUtil(Data* root, const string& firstName)
{
    if (root == nullptr) return root;

    if (firstName < root->_initial.firstName)
    {
        root->left = removeUtil(root->left, firstName);
    }
    else if (firstName > root->_initial.firstName)
    {
        root->right = removeUtil(root->right, firstName);
    }
    else
    {
        if (root->left == nullptr || root->right == nullptr)
        {
            Data* temp = root->left ? root->left : root->right;
            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else
            {
                *root = *temp;
            }
            delete temp;
        }
        else
        {
            Data* temp = minValueNode(root->right);
            root->_initial = temp->_initial;
            root->right = removeUtil(root->right, temp->_initial.firstName);
        }
    }

    if (root == nullptr) return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = balanceFactor(root);

    // Четыре случая несбалансированности, обрабатываемые соответствующими вращениями
    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rotateRight(root);  // Левый левый случай

    if (balance > 1 && balanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);  // Левый правый случай
    }

    if (balance < -1 && balanceFactor(root->right) <= 0)
        return rotateLeft(root);  // Правый правый случай

    if (balance < -1 && balanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);  // Правый левый случай
    }

    return root;
}