/* В5
n= 9
 
stryktyra= название книги, количество страниц, год издания

 klychevoe pole =Количество страниц

 m=20
 sxema xeshirovania =С квадратичной адресацией
 */



#include <iostream>
#include <vector>
#include <list>
#include <string>

// Структура для хранения информации о книге
struct Book {
    std::string title;
    int pageCount;
    int year;

    // Конструктор по умолчанию
    Book() {}

    // Конструктор с параметрами
    Book(std::string _title, int _pageCount, int _year) : title(_title), pageCount(_pageCount), year(_year) {}
};

// Хеш-функция для определения индекса элемента в хеш-таблице
int hashFunction(int value, int tableSize) {
    return value % tableSize;
}

int main() {
    // Создание исходного массива структур из 9 элементов
    std::vector<Book> array(9);
    std::cout << "Введите информацию о книгах:\n";
    for (int i = 0; i < array.size(); i++) {
        std::cout << "Книга #" << i + 1 << ":\n";
        std::cout << "Название: ";
        std::cin >> array[i].title;
        std::cout << "Количество страниц: ";
        std::cin >> array[i].pageCount;
        std::cout << "Год издания: ";
        std::cin >> array[i].year;
        std::cout << "\n";
    }

    // Создание хеш-таблицы из 20 элементов
    const int tableSize = 20;
    std::vector<std::list<Book>> hashTable(tableSize);

    // Заполнение хеш-таблицы
    for (int i = 0; i < array.size(); i++) {
        int index = hashFunction(array[i].pageCount, tableSize);
        hashTable[index].push_back(array[i]);
    }

    // Вывод исходного массива
    std::cout << "Исходный массив:\n";
    for (int i = 0; i < array.size(); i++) {
        std::cout << "Книга #" << i + 1 << ":\n";
        std::cout << "Название: " << array[i].title << "\n";
        std::cout << "Количество страниц: " << array[i].pageCount << "\n";
        std::cout << "Год издания: " << array[i].year << "\n\n";
    }
    std::cout << "\n";

    // Вывод хеш-таблицы
    std::cout << "Хеш-таблица:\n";
    for (int i = 0; i < hashTable.size(); i++) {
        std::cout << "Индекс " << i << ":\n";
        for (const Book& book : hashTable[i]) {
            std::cout << "Название: " << book.title << "\n";
            std::cout << "Количество страниц: " << book.pageCount << "\n";
            std::cout << "Год издания: " << book.year << "\n\n";
        }
    }
    std::cout << "\n";

    // Поиск элемента по количеству страниц в хеш-таблице
    int searchPageCount;
    std::cout << "Введите количество страниц для поиска: ";
    std::cin >> searchPageCount;

    int searchIndex = hashFunction(searchPageCount, tableSize);
    bool found = false;
    for (const Book& book : hashTable[searchIndex]) {
        if (book.pageCount == searchPageCount) {
            found = true;
            std::cout << "Найденная структура:\n";
            std::cout << "Название: " << book.title << "\n";
            std::cout << "Количество страниц: " << book.pageCount << "\n";
            std::cout << "Год издания: " << book.year << "\n";
            break;
        }
    }

    // Вывод результата поиска
    if (found) {
        std::cout << "Книга с указанным количеством страниц найдена в хеш-таблице.\n";
    } else {
        std::cout << "Книга с указанным количеством страниц не найдена в хеш-таблице.\n";
    }

    return 0;
}
