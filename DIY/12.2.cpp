//top 3 with a heap(priority queue)
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

int main() {
    int n;
    cout << "How many numbers? ";
    cin >> n;

    // min-heap: the smallest element is always on top
    priority_queue<int, vector<int>, greater<int>> heap;

    cout << "Enter " << n << " numbers: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        heap.push(x);
        if (heap.size() > 3)
            heap.pop();           // drop the smallest of the four
    }

    // The heap now holds the 3 largest, smallest first
    vector<int> top;
    while (!heap.empty()) {
        top.push_back(heap.top());
        heap.pop();
    }

    cout << "Three largest: ";
    for (int i = (int)top.size() - 1; i >= 0; i--)   // print largest first
        cout << top[i] << " ";
    cout << endl;

    return 0;
}