#include "computer.h"
#include <string>

Computer::Computer(string name, short year, short computerType, short ifBuilt) {
    this -> name = name;
    this -> year = year;
    this -> computerType = computerType;
    this -> ifBuilt = ifBuilt;
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

short Computer::getIfBuilt() {
    return ifBuilt;
}

void Computer::setData(string name, short year, short computerType, short ifBuilt) {
    this -> name = name;
    this -> year = year;
    this -> computerType = computerType;
    this -> ifBuilt = ifBuilt;
}

string Computer::getStoreOutput() {
    string copy = name;
    replace(copy.begin(), copy.end(), ' ', '_' );
    return copy + " " + to_string(year) + " " + to_string(computerType) + " " + to_string(ifBuilt);
}

//type: 0/1 = organize by name, 2 = organize by gender, 3 = organize by birth year, 4 = organize by death year
string Computer::getOutput() {
    ostringstream out;
    string b = (ifBuilt == 0 ? "Not built" : "Built");
    int priorLength  = 0;
    updateString(out, "" + name, priorLength, 0);
    updateString(out, "" + b, priorLength, 28);
    updateString(out, "" + to_string(computerType), priorLength, 12);
    if(ifBuilt >= 0) {
        updateString(out, "" + to_string(ifBuilt), priorLength, 16);
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

