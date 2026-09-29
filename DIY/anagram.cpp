#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string word1, word2;
    cout << "Enter first word: ";
    cin >> word1;
    cout << "Enter second word: ";
    cin >> word2;

    string s1 = word1;
    string s2 = word2;

    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    if (s1 == s2) {
        cout << "\"" << word1 << "\" and \"" << word2 << "\" are anagrams." << endl;
    } else {
        cout << "\"" << word1 << "\" and \"" << word2 << "\" are NOT anagrams." << endl;
    }

    return 0;
}