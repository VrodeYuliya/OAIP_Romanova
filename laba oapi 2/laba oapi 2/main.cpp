/*
Реализовать очередь продуктов в товарном чеке. Товарный чек
содержит список товаров, купленных покупателем в магазине. Один элемент
списка представляет собой пару: товар-сумма. Товар реализовать как структуру
Goods с полями кода и наименования, цены за единицу товара, количества
приобретаемых единиц. Реализовать методы добавления, изменения и удаления
записи о покупаемом виде товара, метод поиска информации об определенном
виде товара по его коду, а также метод подсчета общей суммы, на
которую были осуществлены покупки.
*/
#include <iostream>
#include <string>
using namespace std;

struct Goods {
    int code;
    string name;
    double price;
    int quantity;
};

struct Node {
    Goods data;
    Node* next;
};

 // Очередь
class Queue {
private:
    Node* head;
    Node* tail;

public:
    
    Queue() : head(nullptr), tail(nullptr) {}

    // Добавление нового товара
    void enqueue(Goods g) {
        Node* new_node = new Node{ g, nullptr };
        if (tail == nullptr) {
            head = tail = new_node;
        }
        else {
            tail->next = new_node;
            tail = new_node;
        }
    }
   
    // Удаление товара
    void dequeue() {
        if (head == nullptr) {
            return;
        }
        Node* tmp = head;
        head = head->next;
        delete tmp;
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    //Изменение товара по его коду
    void modify(int code, Goods new_goods) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data.code == code) {
                curr->data = new_goods;
                break;
            }
            curr = curr->next;
        }
    }

    //Поиск товара по его коду
    Node* search(int code) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data.code == code ) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

 
    double total() {
        double sum = 0;
        Node* curr = head;
        while (curr != nullptr) {
            sum += curr->data.price * curr->data.quantity;
            curr = curr->next;
        }
        return sum;
    }

    void print() {
        setlocale(0, "ru");
        if (head == nullptr) {
            cout << "Очередь пуста" << endl;
            return;
        }
        Node* curr = head;
        cout << "Код  Название       Цена  Кол-во" << endl;
        while (curr != nullptr) {
            printf("%-4d %-14s %5.2f %6d\n", curr->data.code, curr->data.name.c_str(), curr->data.price, curr->data.quantity);
            curr = curr->next;
        }
    }
};

int main() {
    setlocale(0, "ru");
    Queue q;
    while (true) {
        cout << "Выберите действие:\n"
        << "1. Добавить товар\n"
        << "2. Удалить товар\n"
        << "3. Изменить товар\n"
        << "4. Поиск товара\n"
        << "5. Общая сумма покупок\n"
        << "6. Вывести список товаров\n"
        << "0. Выход\n"
        << ">> ";
        int choice;
        cin >> choice;
        
        if (choice == 0) {
            break;
        }
        switch (choice) {
            case 1: {
                cout << "Введите данные товара (код, название, цена(за 1 ед.), количество):\n>> ";
                Goods g;
                cin >> g.code >> g.name >> g.price >> g.quantity;
                q.enqueue(g);
                cout << "Товар успешно добавлен в очередь." << endl;
                break;
            }
            case 2: {
                q.dequeue();
                cout << "Товар успешно удален из очереди." << endl;
                break;
            }
            case 3: {
                cout << "Введите код товара, который необходимо изменить:\n>> ";
                int code;
                cin >> code;
                Node* node = q.search(code);
                if (node != nullptr) {
                    cout << "Введите новые данные товара (код, название, цена, количество):\n>> ";
                    Goods g;
                    cin >> g.code >> g.name >> g.price >> g.quantity;
                    q.modify(code, g);
                    cout << "Товар успешно изменен." << endl;
                }
                else {
                    cout << "Товар с таким кодом не найден." << endl;
                }
                break;
            }
            case 4: {
                cout << "Введите код товара для поиска:\n>> ";
                string input;
                cin >> input;
                Node* node = q.search(stoi(input));
                if (node != nullptr) {
                    printf("Товар найден: %d %s %.2f %d\n",  node->data.code, node->data.name.c_str(), node->data.price, node->data.quantity);
                }
                else {
                    cout << "Товар не найден." << endl;
                }
                break;
            }
            case 5: {
                double total = q.total();
                printf("Общая сумма покупок: %.2f\n", total);
                break;
            }
            case 6: {
                q.print();
                break;
            }
            default: {
                cout << "Неверный выбор. Попробуйте еще раз." << endl;
                break;
            }
            }

            cout << endl;
        }

        return 0;
    }

