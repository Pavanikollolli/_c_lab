#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("nums.txt");
    if (!fin) {
        cout << "Error: could not open nums.txt\n";
        return 1;
    }

    int x;
    if (!(fin >> x)) {
        cout << "The file has no integers.\n";
        return 0;
    }

    int count = 1;
    long long sum = x;
    int minVal = x;
    int maxVal = x;

    while (fin >> x) {
        count++;
        sum += x;
        if (x < minVal) minVal = x;
        if (x > maxVal) maxVal = x;
    }
    fin.close();

    cout << "Count = " << count << endl;
    cout << "Sum   = " << sum << endl;
    cout << "Min   = " << minVal << endl;
    cout << "Max   = " << maxVal << endl;
    cout << "Average = " << (double)sum / count << endl;
    return 0;
}