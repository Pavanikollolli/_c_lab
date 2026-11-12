//generic queue
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* head;   // front of the queue
    Node* tail;   // back of the queue
    int count;

public:
    Queue() : head(nullptr), tail(nullptr), count(0) {}

    ~Queue() {
        while (!isEmpty())
            dequeue();
    }

    // Disable copying to avoid a double delete
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void enqueue(const T& value) {
        Node* n = new Node(value);
        if (tail == nullptr)
            head = tail = n;
        else {
            tail->next = n;
            tail = n;
        }
        count++;
    }

    void dequeue() {
        if (isEmpty())
            throw runtime_error("Queue is empty");
        Node* old = head;
        head = head->next;
        if (head == nullptr)
            tail = nullptr;
        delete old;
        count--;
    }

    T& front() {
        if (isEmpty())
            throw runtime_error("Queue is empty");
        return head->data;
    }

    bool isEmpty() const { return head == nullptr; }
    int size() const { return count; }
};

int main() {
    Queue<string> q;

    q.enqueue("Asha");
    q.enqueue("Ravi");
    q.enqueue("Meera");
    cout << "Size: " << q.size() << endl;

    while (!q.isEmpty()) {
        cout << "Front: " << q.front() << endl;
        q.dequeue();
    }

    try {
        q.dequeue();   // empty -> throws
    }
    catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    // The same template works for other types
    Queue<int> qi;
    qi.enqueue(10);
    qi.enqueue(20);
    cout << "\nInt queue front: " << qi.front() << endl;

    return 0;
}