//sort pairs
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    vector<pair<string, int>> v = {
        {"Asha", 91},
        {"Ravi", 78},
        {"Meera", 88},
        {"Kiran", 95},
        {"Divya", 78}
    };

    // Sort by the second field (the int), ascending
    stable_sort(v.begin(), v.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second < b.second;
        });

    for (const auto& p : v)
        cout << p.first << " : " << p.second << endl;

    return 0;
}