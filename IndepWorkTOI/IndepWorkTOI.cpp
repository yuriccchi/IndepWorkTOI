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
    string firstName, lastName, newFirstName, newLastName;
    string searchName;
    int newAge;
    int _stateMenu = -1;
    IndexTree indexTree;
    TreeNode* foundNode;

    //Массивы
    Data* data = new Data[maxSize];
    int* indexes = new int[maxSize];

    while (_stateMenu != 0)
    {
        Menu();
        cin >> _stateMenu;

        switch (_stateMenu)
        {
        case 1:
            dataInput(data, count, indexes);
            break;
        case 2:
            cout << "Данные отсортированные по алфавиту имени (по возрастанию):" << endl;
            printNameAscending(data, indexes, count);
            break;
        case 3:
            cout << "Данные отсортированные по возрасту (по убыванию):" << endl;
            printAgeDescending(data, indexes, count);
            break;
        case 4:
            // Поиск записи
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
            break;
        case 5:
            // Поиск записи
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
            break;
        case 6:
            // Редактирование записи
            cout << "Введите имя и фамилию записи для редактирования: ";
            cin >> firstName >> lastName;
            cout << "Введите новые имя и фамилию: ";
            cin >> newFirstName >> newLastName;
            cout << "Введите новый возраст: ";
            newAge = intInputValue();
            editRecord(data, count, firstName, lastName, newFirstName, newLastName, newAge);
            cout << "Запись успешно отредактирована." << endl;
            break;
        case 7:
            // Удаление записи
            sort(indexes, indexes + count, [&](int a, int b) {
                return compareByName(data[a], data[b]);
                });
            cout << "Введите имя записи для удаления: ";
            cin >> firstName;
            deleteRecord(data, count, indexes, firstName);
            break;
        case 8:
            dataInput(data, count, indexTree);
            break;
        case 9:
            cout << "Данные отсортированные по алфавиту имени (по возрастанию):" << endl;
            printNameAscending(data, indexTree.root);
            break;
        case 10:
            cout << "Данные отсортированные по возрасту (по убыванию):" << endl;
            printAgeDescending(indexTree.root, data);
            break;
        case 11:
            cout << "Введите имя для поиска: ";
            cin >> searchName;
            foundNode = searchByName(indexTree.root, searchName, data);
            break;

        case 12:
            //cout << "Введите возраст для поиска: ";
            //searchAge = intInputValue();
            //foundNode = searchByAge(indexTree.root, searchAge, data);
            //break;
        case 13:
            ///* Редактирование записи
            /*newAge;
            cout << "Введите новые данные для редактирования записи:" << endl;
            cout << "Новое имя: ";
            cin >> newFirstName;
            cout << "Новая фамилия: ";
            cin >> newLastName;
            cout << "Новый возраст: ";
            newAge = intInputValue();
            editRecord(data, indexTree.root, searchName, newFirstName, newLastName, newAge);
            break;*/
        case 14:
            break;
        case 0:
            cout << "Выход из программы" << endl;
            break;
        default:
            cout << "Некорректный ввод. Повторите попытку" << endl;
            break;
        }
    }

    delete[] data;

    return 0;

}