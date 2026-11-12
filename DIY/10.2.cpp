//line numbered copy
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream fin("in.txt");
    if (!fin) {
        cout << "Error: could not open in.txt\n";
        return 1;
    }

    ofstream fout("out.txt");
    if (!fout) {
        cout << "Error: could not create out.txt\n";
        return 1;
    }

    string line;
    int lineNo = 1;

    // getline keeps spaces and handles blank lines
    while (getline(fin, line)) {
        fout << lineNo << ": " << line << endl;
        lineNo++;
    }

    fin.close();
    fout.close();

    cout << "Copied " << (lineNo - 1) << " line(s) to out.txt\n";
    return 0;
}