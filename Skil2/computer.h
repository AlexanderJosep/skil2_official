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
    Computer(string name, short year, short computerType, short ifBulit);
    string getName();
    short getYear();
    short getComputerType();
    short getIfBuilt();
    void setData(string name, short year, short computerType, short ifBuilt);
    string getStoreOutput();
    string getOutput();
private:
    void updateString(ostringstream &o, string data, int &priorLength, int columnSize); // helps with getting ouput string for console
    string name;
    short year;
    short computerType; //0 mechanical, 1 electronic, 2 transistor
    short ifBuilt; //0 not built, 1 built

};

#endif // COMPUTER_H
