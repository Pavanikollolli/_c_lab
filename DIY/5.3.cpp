//unique id factory
#include <iostream>
#include <string>
using namespace std;

class Order {
private:
    int id;
    string item;
    static int nextId;   // next ID to hand out

public:
    Order(const string& itemName) : id(nextId++), item(itemName) {}

    void display() const {
        cout << "Order #" << id << " - " << item << endl;
    }

    int getId() const { return id; }
};

int Order::nextId = 1001;   // first order gets 1001

int main() {
    Order o1("Laptop");
    Order o2("Keyboard");
    Order o3("Monitor");

    o1.display();
    o2.display();
    o3.display();

    return 0;
}