#include <iostream>

using namespace std;

struct QNode {
    int data;
    QNode* next;
    QNode(int d)
    {
        data = d;
        next = NULL;
    }
};

struct Queue {
    QNode* front, * rear;
    Queue() { front = rear = NULL; }
    int size = 0;

    void enQueue(int x)
    {
        size++;
        QNode* temp = new QNode(x);

        if (rear == NULL) {
            front = rear = temp;
            return;
        }
        rear->next = temp;
        rear = temp;
    }

    void deQueue()
    {
        size--;
        if (front == NULL)
            return;

        QNode* temp = front;
        front = front->next;

        if (front == NULL)
            rear = NULL;

        delete (temp);
    }
    int first() {
        return front->data;
    }
    void Print() {
        QNode* p;
        p = front;
        while (p != nullptr) {
            cout << p->data << "\t";
            p = p->next;
        }
        cout << endl;
    }
};

Queue merge(Queue first, Queue second) {
    int new_size = first.size + second.size;
    Queue new_queue;
    for (int i = 0; i < new_size / 2; i++) {
        new_queue.enQueue(first.first());
        new_queue.enQueue(second.first());
        first.deQueue();
        second.deQueue();
    }
    return new_queue;
}

int main()
{
    Queue q;
    Queue q2;
    q.enQueue(5);
    q.enQueue(15);
    q.enQueue(25);
    q.enQueue(35);
    q.enQueue(45);
    q2.enQueue(10);
    q2.enQueue(20);
    q2.enQueue(30);
    q2.enQueue(40);
    q2.enQueue(50);
    q.Print();
    q2.Print();
    Queue new_q = merge(q, q2);
new_q.Print();
}