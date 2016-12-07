#ifndef COMPUTER_H
#define COMPUTER_H
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

class Computer {
public:
    Computer(string name, short year, short computerType, bool built);
    string getName();
    short getYear();
    short getComputerType();
    short getBuilt();
    void setData(string name, short year, short computerType, bool built);
    string getOutput();
private:
    void updateString(ostringstream &o, string data, int &priorLength, int columnSize); // helps with getting ouput string for console
    string name;
    short year;
    short computerType; //0 mechanical, 1 electronic, 2 transistor
    bool built; //0 not built, 1 built
};

#endif // COMPUTER_H
