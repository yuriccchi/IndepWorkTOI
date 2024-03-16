#include "Functions.h"
#include <iostream>
#include <string>
#include <algorithm>

void Menu()
{    
    cout << "Выберите действие: " << endl
        << "1. Ввод данных (Индекс-массив)" << endl
        << "2. Вывод данных, отсортированных по алфавиту (Индекс-массив)" << endl
        << "3. Вывод данных, отсортированных по возрасту (Индекс-массив)" << endl
        << "4. Поиск по имени (Индекс-массив)" << endl
        << "5. Поиск по возрасту (Индекс-массив)" << endl
        << "6. Редактирование записи (Индекс-массив)" << endl
        << "7. Удаление записи (Индекс-массив)" << endl
        << "8. Ввод данных (Бинарное дерево)" << endl
        << "9. Вывод данных, отсортированных по алфавиту (Бинарное дерево)" << endl
        << "10. Вывод данных, отсортированных по возрасту (Бинарное дерево)" << endl
        << "11. Поиск по имени (Бинарное дерево)" << endl
        << "12. Поиск по возрасту (Бинарное дерево)" << endl
        << "13. Редактирование записи (Бинарное дерево)" << endl
        << "14. Удаление записи (Бинарное дерево)" << endl
        << "15. Ввод данных (Линейный список)" << endl
        << "16. Вывод данных в изначальном порядке (Линейный список)" << endl
        << "17. Вывод данных, отсортированных по имени (Линейный список)" << endl
        << "18. Вывод данных, отсортированных по возрасту (Линейный список)" << endl
        << "19. Поиск по имени (Линейный список)" << endl
        << "20. Поиск по возрасту (Линейный список)" << endl
        << "21. Удаление записи (Линейный сипсок)" << endl
        << "0. Выход" << endl
        << "Ваш выбор: ";
}

int main()
{
    //руссификация консоли
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Инициализация нужных переменных
    int maxSize = 200;
    int count = 0;
    string firstName, lastName, newFirstName, newLastName, gift;
    string searchName;
    int day, month;
    int newAge;
    int _stateMenu = -1;

    // Массивы
    Data* data = new Data[maxSize];
    int* indexes = new int[maxSize];

    // Деревья индексов
    Data* binaryData = new Data[0];
    AgeTreeNode* rootByAge = nullptr; // Изменение инициализации
    NameTreeNode* rootByFirstName = nullptr; // Изменение инициализации
    int binarySize = 0;

    // Линейный список
    Node* head = nullptr;
    int lineSize = 0;

    while (_stateMenu != 0)
    {
        Menu();
        cin >> _stateMenu;

        switch (_stateMenu)
        {
        case 1:
            dataInput(data, count, indexes);
            cout << endl;
            break;
        case 2:
            cout << "Данные отсортированные по алфавиту имени (по возрастанию):" << endl;
            printNameAscending(data, indexes, count);
            cout << endl;
            break;
        case 3:
            cout << "Данные отсортированные по возрасту (по убыванию):" << endl;
            printAgeDescending(data, indexes, count);
            cout << endl;
            break;
        case 4:
            cout << "Введите имя для поиска: ";
            cin >> searchName;
            {
                sort(indexes, indexes + count, [&](int a, int b) {
                    return compareByName(data[a], data[b]);
                    });

                int pos = binarySearchByName(data, indexes, searchName, 0, count - 1, nameComparator);
                if (pos != -1) {
                    cout << "Найденная запись:" << endl;
                    cout << data[indexes[pos]]._initial.firstName << " " << data[indexes[pos]]._initial.lastName << ", возраст: " << data[indexes[pos]]._age.age << " лет" << endl;
                }
                else {
                    cout << "Запись с указанным именем не найдена" << endl;
                }
            }
            cout << endl;
            break;
        case 5:
            int searchAge;
            cout << "Введите возраст для поиска: ";
            searchAge = intInputValue();
            {
                sort(indexes, indexes + count, [&](int a, int b) {
                    return compareByAge(data[a], data[b]);
                    });

                int pos = binarySearchByAge(data, indexes, count, searchAge, ageComparator);
                if (pos != -1) {
                    cout << "Найденная запись:" << endl;
                    cout << data[indexes[pos]]._initial.firstName << " " << data[indexes[pos]]._initial.lastName << ", возраст: " << data[indexes[pos]]._age.age << " лет" << endl;
                }
                else {
                    cout << "Запись с указанным возрастом не найдена" << endl;
                }
            }
            cout << endl;
            break;
        case 6:
            cout << "Введите имя и фамилию записи для редактирования: ";
            cin >> firstName >> lastName;
            cout << "Введите новые имя и фамилию: ";
            cin >> newFirstName >> newLastName;
            cout << "Введите новые месяц и день дня рождения: ";
            month = intInputMonth();
            day = intInputDay(month);          
            cout << "Введите новый возраст: ";
            newAge = intInputValue();
            editRecord(data, count, firstName, lastName, newFirstName, newLastName, newAge);
            cout << "Запись успешно отредактирована" << endl;
            cout << endl;
            break;
        case 7:
            sort(indexes, indexes + count, [&](int a, int b) {
                return compareByName(data[a], data[b]);
                });
            cout << "Введите имя записи для удаления: ";
            cin >> firstName;
            deleteRecord(data, count, indexes, firstName);
            cout << endl;
            break;
        case 8:
            cout << "Введите количество вводимых сейчас данных: ";
            int newDataCount;
            cin >> newDataCount;

            for (int i = 0; i < newDataCount; i++)
            {
                cout << "Введите имя и фамилию: ";
                cin >> firstName >> lastName;

                cout << "Введите месяц и день дня рождения: ";              
                month = intInputMonth();
                day = intInputDay(month);

                cout << "Введите, сколько лет сейчас вашему другу: ";
                newAge = intInputValue();

                cout << "Введите, какие подарки любит ваш друг: ";
                cin >> gift;

                cout << "___________________________" << endl;

                Data record = { {firstName, lastName}, {day, month}, {newAge}, {gift} };
                insertRecord(binaryData, rootByAge, rootByFirstName, record, binarySize);
            }
            cout << endl;
            break;
        case 9:
            cout << "Данные отсортированные по алфавиту имени (по возрастанию):" << endl;
            printAscendingByFirstName(binaryData, rootByFirstName);
            cout << endl;
            break;
        case 10:
            cout << "Данные отсортированные по возрасту (по убыванию):" << endl;
            printDescendingByAge(binaryData, rootByAge);
            cout << endl;
            break;
        case 11:
            cout << "Введите имя для поиска: ";
            cin >> firstName;
            searchByFirstName(binaryData, rootByFirstName, firstName);
            cout << endl;
            break;
        case 12:
            int age;
            cout << "Введите возраст для поиска: ";
            age = intInputValue();
            searchByAge(binaryData, rootByAge, age);
            cout << endl;
            break;
        case 13:
            cout << "Введите имя для поиска: ";
            cin >> firstName;
            editRecordbyName(binaryData, rootByFirstName, firstName);
            cout << endl;
            break;
        case 14:
            cout << "Введите имя для поиска: ";
            cin >> firstName;
            deleteRecordByName(rootByFirstName, firstName);
            cout << endl;
            break;
        case 15:
            cout << "Введите количество вводимых сейчас данных: ";
            cin >> lineSize;

            for (int i = 0; i < lineSize; i++)
            {
                cout << "Введите имя и фамилию: ";
                cin >> firstName >> lastName;

                cout << "Введите месяц и день дня рождения: ";
                month = intInputMonth();
                day = intInputDay(month);

                cout << "Введите, сколько лет сейчас вашему другу: ";
                newAge = intInputValue();

                cout << "Введите, какие подарки любит ваш друг: ";
                cin >> gift;

                cout << "___________________________" << endl;

                Data record = { {firstName, lastName}, {day, month}, {newAge}, {gift} };
                insert(head, record);
            }
            cout << endl;
            break;
        case 16:
            cout << "Данные:" << endl;
            printList(head);
            cout << endl;
            break;
        case 17:
            cout << "Данные отсортированные по алфавиту имени (по возрастанию):" << endl;
            sortByFirstName(head);
            printList(head);
            cout << endl;
            break;
        case 18:
            cout << "Данные отсортированные по возрасту (по убыванию):" << endl;
            sortByAge(head);
            printList(head);
            cout << endl;
            break;
        case 19:
            cout << "Введите имя для поиска: ";
            cin >> firstName;
            searchByName(head, firstName);
            cout << endl;
            break;
        case 20:
            cout << "Введите возраст для поиска: ";
            age = intInputValue();
            searchByAge(head, age);
            cout << endl;
            break;
        case 21:
            cout << "Введите имя для поиска и удаления: ";
            cin >> firstName;
            deleteByName(head, firstName);
            cout << endl;
            break;
        case 0:
            cout << "Выход из программы" << endl;
            break;
        default:
            cout << "Некорректный ввод. Повторите попытку" << endl;
            break;
        }
    }

    //delete[] data;
    //delete[]

    return 0;

}