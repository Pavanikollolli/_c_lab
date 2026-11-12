//prove the race
#include <iostream>
#include <mutex>
#include <thread>

int counter = 0;
std::mutex mtx;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        // UNCOMMENT THE LINE BELOW TO RESTORE THE LOCK AND GET 200000:
        // std::lock_guard<std::mutex> lock(mtx);
        
        ++counter;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << " (Expected: 200000)\n";
    return 0;
}