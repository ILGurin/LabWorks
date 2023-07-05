#include <iostream>
#include <string>
#include <Windows.h>
#include <stdlib.h>

using namespace std;

template <typename T>
struct NodeStack {
    T item;
    NodeStack<T>* next;
};
template <typename T>

class StackList {
private:
    NodeStack<T>* pTop; // указатель на вершину стека
public:
    StackList() { pTop = nullptr; }
    void Push(T item) {
        NodeStack<T>* p;
        try {
            p = new NodeStack<T>;
        }
        catch (bad_alloc e)
        {
            cout << e.what() << endl;
            return;
        }
        p->item = item;
        p->next = pTop;
        pTop = p;
    }

    // очищает стек
    void Empty()
    {
        NodeStack<T>* p;
        NodeStack<T>* p2;

        p = pTop;

        while (p != nullptr)
        {
            p2 = p;
            p = p->next;
            delete p2;
        }
        pTop = nullptr;
    }

    ~StackList()
    {
        Empty();
    }

    //Обращение к N-ому элементу стека
    char Element(int N) {
        NodeStack<T>* p;
        p = pTop;
        for (int i = 0; i < N-1; i++) {
            p = p->next;
        }
        return p->item;
    }

    //Обращение к первому элементу стека
    char Top(const char* objName) {
        NodeStack<T>* p;
        p = pTop;
        return p->item;
    }

    //Проверка на заполненность (если пустой, возвращает true)
    bool empty() {
        return pTop == nullptr;
    }

    // метод, удаляющий элемент со стека
    T Pop()
    {
        if (pTop == nullptr)
            return 0;

        NodeStack<T>* p2;
        T item;
        item = pTop->item;

        p2 = pTop;
        pTop = pTop->next;

        delete p2;

        return item;
    }
};

bool check_HTML(std::string html) {
    StackList<char> SL;
    int count = 0;
    for (char c : html) {
        std::string skip = { "/, xyzabcdefghijklmnopqrstuvw" };
        bool a = true;
        for (int i = 0; i < skip.size(); i++) {
            if (c == skip[i]) {
                a = false;
                break;
            }
        }

        if (a == false) {
            continue;
        }

        if (c == '<') {
            SL.Push(c);
            continue;
        }

        if (SL.empty()) {
            return false;
        }

        if (c == '>' && SL.Top("SL") != '<')
            return false;
        count++;
        SL.Pop();
    }
    if (count % 2 == 0) {
        return true;
    }
    else {
        return false;
    }
}

void Menu() {
    int answer;
    while (true) {
        std::cout << "Выберите действие: \n1. Проверить HTML код\n2. Выход\n";
        std::cin >> answer;
        string code;
        switch (answer) {
        case 1:
            std::cout << "Введите HTML код: ";
            std::cin >> code;
            if (check_HTML(code)) {
                std::cout << "Ошибок нет!!!\n";
            }
            else {
                std::cout << "Есть ошибка...\n";
            }
            break;
        case 2:
            exit(0);
            break;
        default:
            std::cout << "Некоректный ответ, попробуйте снова. ";
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    Menu();
    return 0;
}