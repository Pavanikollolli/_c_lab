#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <cctype>
using namespace std;

// Lowercase the word and strip punctuation so "Hello," and "hello" match
string clean(const string& w) {
    string result;
    for (char c : w)
        if (isalnum((unsigned char)c))
            result += tolower((unsigned char)c);
    return result;
}

int main() {
    cout << "Enter some words (press Enter when done):\n";
    string line;
    getline(cin, line);

    unordered_map<string, int> freq;
    istringstream words(line);
    string w;

    while (words >> w) {
        string cw = clean(w);
        if (!cw.empty())
            freq[cw]++;
    }

    if (freq.empty()) {
        cout << "No words entered.\n";
        return 0;
    }

    cout << "\nWord counts:\n";
    for (const auto& p : freq)
        cout << p.first << " : " << p.second << endl;

    // Find the most frequent word
    string best;
    int bestCount = 0;
    for (const auto& p : freq) {
        if (p.second > bestCount) {
            bestCount = p.second;
            best = p.first;
        }
    }

    cout << "\nMost frequent word: \"" << best << "\" ("
         << bestCount << " times)\n";
    return 0;
}