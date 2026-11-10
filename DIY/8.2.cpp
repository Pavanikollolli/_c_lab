//polymorphic logger
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Logger {
public:
    virtual ~Logger() {}
    virtual void write(const string& msg) = 0;   // pure virtual
};

class ConsoleLogger : public Logger {
public:
    void write(const string& msg) override {
        cout << "[console] " << msg << endl;
    }
};

class FileLogger : public Logger {
private:
    ofstream file;

public:
    FileLogger(const string& filename) {
        file.open(filename, ios::app);
    }
    ~FileLogger() { if (file.is_open()) file.close(); }

    void write(const string& msg) override {
        file << msg << endl;
        cout << "[file] wrote to log file" << endl;
    }
};

int main() {
    Logger* logger = new ConsoleLogger();
    logger->write("Application started");

    // Switch implementation at run time
    delete logger;
    logger = new FileLogger("app.log");
    logger->write("Now logging to a file");
    logger->write("Second file entry");

    delete logger;
    logger = new ConsoleLogger();
    logger->write("Back to the console");

    delete logger;
    return 0;
}
