#include <iostream>
using namespace std;

class Matrix {
private:
    int rows, cols;
    int** data;

public:
    // Allocate an m x n grid with new
    Matrix(int m, int n) : rows(m), cols(n) {
        data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++)
                data[i][j] = 0;
        }
        cout << "Matrix constructed (" << rows << "x" << cols << ")\n";
    }

    // Deep copy constructor: new memory, copy the values
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++)
                data[i][j] = other.data[i][j];
        }
        cout << "Matrix deep-copied\n";
    }

    // Free everything in the destructor
    ~Matrix() {
        for (int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
        cout << "Matrix destroyed\n";
    }

    void set(int i, int j, int value) { data[i][j] = value; }

    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << data[i][j] << "\t";
            cout << endl;
        }
    }
};

int main() {
    Matrix a(2, 3);
    int v = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            a.set(i, j, v++);

    Matrix b = a;        // calls the deep copy constructor
    b.set(0, 0, 99);     // changing b must NOT change a

    cout << "Matrix a:\n"; a.display();
    cout << "Matrix b:\n"; b.display();
    return 0;
}