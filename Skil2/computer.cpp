#include "computer.h"
#include <string>

Computer::Computer(string name, short year, short computerType, bool built) {
    this -> name = name;
    this -> year = year;
    this -> computerType = computerType;
    this -> built = built;
}

string Computer::getName() {
    return name;
}

short Computer::getYear() {
    return year;
}

short Computer::getComputerType() {
    return computerType;
}

short Computer::getBuilt() {
    return built;
}

void Computer::setData(string name, short year, short computerType, bool built) {
    this -> name = name;
    this -> year = year;
    this -> computerType = computerType;
    this -> built = built;
}

string Computer::getOutput() {
    ostringstream out;
    string b = (built == 0 ? "Not built" : "Built");
    int priorLength  = 0;
    updateString(out, "" + name, priorLength, 0);
    updateString(out, "" + b, priorLength, 28);
    updateString(out, "" + to_string(computerType), priorLength, 12);
    if(built >= 0) {
        updateString(out, "" + to_string(built), priorLength, 16);
    }
    return out.str();
}

void Computer::updateString(ostringstream &o, string data, int &priorLength, int columnSize) {
    if(o.tellp() > 0 && priorLength < 30) {
        o << setw(columnSize - (priorLength - data.length()));
    }
    o << data;
    priorLength = data.length();
}

