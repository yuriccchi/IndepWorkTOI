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
int intInputDay(int month)
{
    int day;
    int maxDays = 31; // Максимальное количество дней по умолчанию

    // Определяем максимальное количество дней в месяце
    switch (month)
    {
    case 4: // Апрель
    case 6: // Июнь
    case 9: // Сентябрь
    case 11: // Ноябрь
        maxDays = 30;
        break;
    case 2: // Февраль
        maxDays = 28; // Предполагаем, что это не високосный год
        break;
    }

    // Ввод значения дня с проверкой корректности
    do
    {
        while (!(std::cin >> day) || day < 1 || day > maxDays)
        {
            std::cout << "Ошибка ввода. Введите номер для от 1 до " << maxDays << std::endl;
            std::cin.clear();
            std::cin.ignore(32767, '\n');
        }
    } while (day < 1 || day > maxDays);

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

        cout << "Введите месяц и день дня рождения: ";      
        newData[i]._date.month = intInputMonth();
        newData[i]._date.day = intInputDay(newData[i]._date.month);

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
        cout << data[indexes[i]]._initial.firstName << " " << data[indexes[i]]._initial.lastName << ", возраст: " << data[indexes[i]]._age.age << " лет" << ", любимые подарки: " << data[indexes[i]]._loveGifts.loveGifts << endl;
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
        cout << data[indexes[i]]._initial.firstName << " " << data[indexes[i]]._initial.lastName << ", возраст: " << data[indexes[i]]._age.age << " лет" << ", любимые подарки: " << data[indexes[i]]._loveGifts.loveGifts << endl;
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

        Data* newData = new Data[newSize];
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
                newData[i] = data[i];
            else
                newData[i] = data[i + 1];
        }

        data = newData;
        indexes = newIndexes;
        count = newSize;
    }
}

// Вставка данных в дерево (Бинарное дерево)
void insertRecord(Data*& records, AgeTreeNode*& rootByAge, NameTreeNode*& rootByFirstName, const Data& record, int& size)
{
    // Создание нового массива с увеличенным размером
    Data* newRecords = new Data[size + 1];

    // Копирование старых записей
    for (int i = 0; i < size; ++i)
    {
        newRecords[i] = records[i];
    }    

    // Добавление новой записи
    newRecords[size] = record;

    // Удаление старого массива
    delete[] records;
    records = newRecords;

    ++size; // Увеличение размера
    int index = size - 1; // Индекс новой записи

    // Добавление в бинарное дерево по возрасту
    if (rootByAge == nullptr)
    {
        rootByAge = new AgeTreeNode(record._age.age, index);
    }     
    else
    {
        insertNodeByAge(rootByAge, record._age.age, index);
    }
        
    // Добавление в бинарное дерево по имени
    if (rootByFirstName == nullptr)
    {
        rootByFirstName = new NameTreeNode(record._initial.firstName, index);
    }     
    else
    {
        insertNodeByFirstName(rootByFirstName, record._initial.firstName, index);
    }    
}

// Вставка узла по возрасту (Бинарное дерево)
void insertNodeByAge(AgeTreeNode* node, int age, int index) 
{
    if (age < node->age) // Если возраст меньше, чем у текущего узла
    {
        if (node->left == nullptr) // Если левое поддерево пусто, создаем новый узел и вставляем его туда
        {
            node->left = new AgeTreeNode(age, index);
        }
        else // Иначе рекурсивно вставляем новый узел в левое поддерево
        {
            insertNodeByAge(node->left, age, index);
        }
    }
    else // Аналогично с правым
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

// Вставка узла по имени (Бинарное дерево)
void insertNodeByFirstName(NameTreeNode* node, const string& firstName, int index) 
{
    if (firstName < node->firstName) //Если имя меньше, чем у текущего узла
    {
        if (node->left == nullptr) // Если левое поддерево пусто, создаем новый узел и вставляем его туда
        {
            node->left = new NameTreeNode(firstName, index);
        }        
        else // Иначе рекурсивно вставляем новый узел в левое поддерево
        {
            insertNodeByFirstName(node->left, firstName, index);
        }          
    }
    else // Аналогично с правым
    {
        if (node->right == nullptr)
        {
            node->right = new NameTreeNode(firstName, index);
        }
        else
        {
            insertNodeByFirstName(node->right, firstName, index);
        }         
    }
}

// Печать по убыванию возраста (Бинарное дерево)
void printDescendingByAge(Data* records, AgeTreeNode* rootByAge)
{
    InorderTraversalByAge(records, rootByAge);
}

// Вспомогательная функция для обхода дерева по возрасту и печати узлов
void InorderTraversalByAge(Data* records, AgeTreeNode* node)
{
    if (node != nullptr)
    {
        InorderTraversalByAge(records, node->right); // Рекурсивно обходим правое поддерево
        printRecord(records, node->index); // Печатаем данные текущего узла
        InorderTraversalByAge(records, node->left); // Рекурсивно обходим левое поддерево
    }
}

// Печать по возрастанию имени (по алфавиту) (Бинарное дерево)
void printAscendingByFirstName(Data* records, NameTreeNode* rootByFirstName)
{
    InorderTraversalByFirstName(records, rootByFirstName);
}

// Вспомогательная функция для обхода дерева по имени и печати узлов (Бинарное дерево)
void InorderTraversalByFirstName(Data* records, NameTreeNode* node) {
    if (node != nullptr)
    {
        InorderTraversalByFirstName(records, node->left); // Рекурсивно обходим левое поддерево
        printRecord(records, node->index); // Печатаем данные текущего узла
        InorderTraversalByFirstName(records, node->right); // Рекурсивно обходим правое поддерево
    }
}

// Функция печати данных из массива (Бинарное дерево)
void printRecord(Data* records, int index)
{
    Data record = records[index];
    cout << record._initial.firstName << " " << record._initial.lastName << ", возраст: " << record._age.age << " лет" << ", любимые подарки: " << record._loveGifts.loveGifts << endl;
}

// Поиск по возрасту (Бинарное дерево)
void searchByAge(Data* records, AgeTreeNode* rootByAge, int age)
{
    AgeTreeNode* result = searchNodeByAge(rootByAge, age);
    if (result != nullptr)
    {
        printRecord(records, result->index);
    }      
    else
    {
        cout << "Запись с указанным возрастом не найдена" << endl;
    }       
}

// Поиск по имени (Бинарное дерево)
void searchByFirstName(Data* records, NameTreeNode* rootByFirstName, const string& firstName)
{
    NameTreeNode* result = searchNodeByFirstName(rootByFirstName, firstName);
    if (result != nullptr)
    {
        printRecord(records, result->index);
    }  
    else
    {
        cout << "Запись с указанным именем не найдена" << endl;
    }     
}

// Вспомогательная функция для поиска по возрасту (Бинарное дерево)
AgeTreeNode* searchNodeByAge(AgeTreeNode* node, int age)
{
    if (node == nullptr || node->age == age)
    {
        return node;
    }
        
    if (age < node->age)
    {
        return searchNodeByAge(node->left, age); // Поиск в левом поддереве
    }      
    else
    {
        return searchNodeByAge(node->right, age); // Поиск в правом поддереве
    }      
}

// Вспомогательная функция для поиска по имени (Бинарное дерево)
NameTreeNode* searchNodeByFirstName(NameTreeNode* node, const string& firstName)
{
    if (node == nullptr || node->firstName == firstName)
    {
        return node;
    }     

    if (firstName < node->firstName)
    {
        return searchNodeByFirstName(node->left, firstName); // Поиск в левом поддереве
    }
    else
    {
        return searchNodeByFirstName(node->right, firstName); // Поиск в правом поддереве
    }       
}

// Редактирование записи по имени (Бинарное дерево)
void editRecordbyName(Data* records, NameTreeNode* root, string firstName)
{
    NameTreeNode* result = searchNodeByFirstName(root, firstName);
    Data data;

    if (result != nullptr) // Обновление данных
    {
        cout << "Введите новые имя и фамилию: ";
        cin >> data._initial.firstName >> data._initial.lastName;

        cout << "Введите месяц и день дня рождения: ";      
        data._date.month = intInputMonth();
        data._date.day = intInputDay(data._date.month);

        cout << "Введите, сколько лет сейчас вашему другу: ";
        data._age.age = intInputValue();

        cout << "Введите, какие подарки любит ваш друг: ";
        cin >> data._loveGifts.loveGifts;

        records[result->index] = data;
        result->firstName = data._initial.firstName;

        cout << "Запись успешно отредактирована" << endl;
    }
    else
    {
        cout << "Данные не найдены" << endl;
    }
}

// Функция удаления по имени (Бинарное дерево)
void deleteRecordByName(NameTreeNode*& root, string firstName)
{
    deleteNodeByName(root, firstName);
}

// Вспомогательная функция для удаления узла по имени в дереве (Бинарное дерево)
NameTreeNode* deleteNodeByName(NameTreeNode*& node, string firstName)
{
    if (node == nullptr)
    {
        return node;
    }   

    if (firstName < node->firstName)
    {
        node->left = deleteNodeByName(node->left, firstName);
    }        
    else if (firstName > node->firstName)
    {
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

// Поиск узла с минимальным возрастом в дереве (Бинарное дерево)
NameTreeNode* findMinName(NameTreeNode* node)
{
    while (node->left != nullptr)
        node = node->left;

    return node;
}

// Поиск узла с минимальным именем в дереве (Бинарное дерево)
AgeTreeNode* findMinAge(AgeTreeNode* node)
{
    while (node->left != nullptr)
        node = node->left;

    return node;
}

// Функция для вставки элемента в конец списка
void insert(LinkedList*& head, Data data)
{
    LinkedList* newNode = new LinkedList;
    newNode->data = data;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    LinkedList* temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

// Функция для сортировки списка по возрастанию имени
void sortByFirstName(LinkedList*& head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    LinkedList* sorted = nullptr;
    LinkedList* current = head;

    while (current != nullptr)
    {
        LinkedList* next = current->next;

        if (sorted == nullptr || sorted->data._initial.firstName >= current->data._initial.firstName)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            LinkedList* temp = sorted;
            while (temp->next != nullptr && temp->next->data._initial.firstName < current->data._initial.firstName)
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    head = sorted;
}

// Функция для сортировки списка по убыванию возраста
void sortByAge(LinkedList*& head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }        

    LinkedList* sorted = nullptr;
    LinkedList* current = head;

    while (current != nullptr)
    {
        LinkedList* next = current->next;

        if (sorted == nullptr || sorted->data._age.age <= current->data._age.age)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            LinkedList* temp = sorted;
            while (temp->next != nullptr && temp->next->data._age.age > current->data._age.age)
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    head = sorted;
}

// Функция для печати записей списка
void printList(LinkedList* head)
{
    LinkedList* temp = head;

    if (temp == nullptr)
    {
        cout << "База данных пуста" << endl;
    }

    while (temp != nullptr)
    {
        cout << temp->data._initial.firstName << " " << temp->data._initial.lastName << ", " << temp->data._age.age << " лет, " << temp->data._loveGifts.loveGifts << endl;
        temp = temp->next;
    }
}

// Функция для поиска записей по имени
void searchByName(LinkedList* head, string name)
{
    sortByFirstName(head);
    bool found = false;

    LinkedList* temp = head;
    while (temp != nullptr)
    {
        if (temp->data._initial.firstName == name)
        {
            cout << "найденная запись:" << endl;
            cout << temp->data._initial.firstName << " " << temp->data._initial.lastName << ", " << temp->data._age.age << " лет, " << " любимый подарок: " << temp->data._loveGifts.loveGifts << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "Запись с заданным именем не найдена" << endl;
    }
}

// Функция для поиска записей по возрасту
void searchByAge(LinkedList* head, int age)
{
    sortByAge(head);
    bool found = false;

    LinkedList* temp = head;
    while (temp != nullptr)
    {
        if (temp->data._age.age == age)
        {
            cout << "найденная запись:" << endl;
            cout << temp->data._initial.firstName << " " << temp->data._initial.lastName << ", " << temp->data._age.age << " лет, " << " любимый подарок: " << temp->data._loveGifts.loveGifts << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "Запись с заданным возрастом не найдена" << endl;
    }
}

// Функция для удаления записи по имени
void deleteByName(LinkedList*& head, string name)
{
    sortByFirstName(head);

    LinkedList* temp = head;
    LinkedList* prev = nullptr;

    while (temp != nullptr && temp->data._initial.firstName != name)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr)
    {
        cout << "Запись с заданным именем не найдена" << endl;
        return;
    }

    if (prev == nullptr)
    {
        head = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }

    delete temp;
    cout << "Запись удалена" << endl;
}