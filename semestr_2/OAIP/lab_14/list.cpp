#include <iostream>
#include <Windows.h> 
 
using namespace std; 
 
 
struct Node { 
    int data; 
    Node* next; 
}; 
 
 
Node* createNode(int value) { 
    Node* newNode = new Node(); 
    if (newNode == nullptr) { 
        cout << "Ошибка: не удалось выделить память\n"; 
        exit(1); 
    } 
    newNode->data = value; 
    newNode->next = nullptr; 
    return newNode; 
} 
 
 
void addToTail(Node** head, int value) { 
    Node* newNode = createNode(value); 
    if (*head == nullptr) { 
        *head = newNode; 
        newNode->next = *head; 
    } 
    else { 
        Node* temp = *head; 
        while (temp->next != *head) { 
            temp = temp->next; 
        } 
        temp->next = newNode; 
        newNode->next = *head; 
    } 
    cout << "Элемент " << value << " добавлен в хвост списка\n"; 
} 
 
 
void printList(Node* head) { 
    if (head == nullptr) { 
        cout << "Список пуст\n"; 
        return; 
    } 
    cout << "Элементы списка: "; 
    Node* temp = head; 
    do { 
        cout << temp->data << " "; 
        temp = temp->next; 
    } while (temp != head); 
    cout << endl; 
} 
 
 
void deleteFromNtoK(Node** head, int N, int K) { 
    if (*head == nullptr) { 
        cout << "Список пуст\n"; 
        return; 
    } 
    if (N >= K) { 
        cout << "Ошибка: некорректные значения N и K\n"; 
        return; 
    } 
    Node* temp = *head; 
    Node* prev = nullptr; 
    int count = 0; 
    while (count < N && temp->next != *head) { 
        prev = temp; 
        temp = temp->next; 
        count++; 
    } 
    if (count != N) { 
        cout << "Ошибка: позиция N выходит за пределы списка\n"; 
        return; 
    } 
    count = 0; 
    while (count < K - N && temp->next != *head) { 
        Node* nextNode = temp->next; 
        if (prev == nullptr) { 
            *head = nextNode; 
        } 
        delete temp; 
        temp = nextNode; 
        count++; 
    } 
    if (count != K - N) { 
        cout << "Ошибка: позиция K выходит за пределы списка\n"; 
        return; 
    } 
    if (prev != nullptr) { 
        prev->next = temp; 
    } 
    if (temp == *head) { 
        *head = nullptr; 
    } 
    cout << "Элементы с позиции " << N << " по " << K - 1 << " удалены из списка\n"; 
} 
 
int main() { 
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    Node* head = nullptr; 
 
    int choice; 
    do { 
        cout << "\n Однонаправленный циклический список\n"; 
        cout << "1. Добавить элемент в хвост списка\n"; 
        cout << "2. Просмотреть список\n"; 
        cout << "3. Удалить элементы с позиции N по K\n"; 
        cout << "0. Выход\n"; 
        cout << "Выберите действие: "; 
        cin >> choice; 
 
        switch (choice) { 
        case 0: 
            cout << "Выход\n"; 
            break; 
        case 1: 
            int value; 
            cout << "Введите значение элемента: "; 
            cin >> value; 
            addToTail(&head, value); 
            break; 
        case 2: 
            printList(head); 
            break; 
        case 3: 
            int N, K; 
            cout << "Введите позицию N: "; 
            cin >> N; 
            cout << "Введите позицию K: "; 
            cin >> K; 
            deleteFromNtoK(&head, N, K); 
            break; 
        default: 
            cout << "Ошибка: некорректный выбор\n"; 
            break; 
        } 
    } while (choice != 0); 
 
    return 0; 
}