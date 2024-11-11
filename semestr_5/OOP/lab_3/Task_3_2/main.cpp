#include <QCoreApplication>
#include <iostream>

using namespace std;

class Node {
public:
    int value = 0;
    Node *next = nullptr;
};

void insert(Node*& head, int newValue) {
    Node* newNode = new Node();
    newNode->value = newValue;
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void display(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void sort(Node*& head) {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node* sorted = nullptr;

    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next; // Сохраняем следующий узел
        if (sorted == nullptr || sorted->value >= current->value) {
            // Вставляем в начало отсортированного списка
            current->next = sorted;
            sorted = current;
        } else {
            // Находим место для вставки
            Node* temp = sorted;
            while (temp->next != nullptr && temp->next->value < current->value) {
                temp = temp->next;
            }
            current->next = temp->next; // Вставляем текущий узел
            temp->next = current;
        }
        current = nextNode; // Переходим к следующему узлу
    }

    head = sorted;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int size;
    cout << "Enter the list size: ";
    cin >> size;

    Node *root = new Node;
    root->value = rand() % 9 + 1;
    for(int i = 1; i < size; i++) {
        insert(root, rand() % 9 + 1);
    }

    cout << "Original list: ";
    display(root);
    sort(root);
    cout << "Sorted list: ";
    display(root);

    return a.exec();
}
