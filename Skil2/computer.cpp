#include "computer.h"

Computer::Computer(string name, short year, short type) {
    this -> name = name;
    this -> year = year;
    this -> type = type;
}

short Computer::getYear() {
    return year;
}

short Computer::getType() {
    return type;
}

void Computer::setData(string name, short year, short type) {
    this -> name = name;
    this -> year = year;
    this -> type = type;
}

string Computer::getOutput() {
    ostringstream out;
    int priorLength  = 0;
    updateString(out, name, priorLength, 0);
    updateString(out, MACHINE_TYPES[type], priorLength, 28);
    updateString(out, (year < 0 ? "Not built" : to_string(year)), priorLength, 19);
    return out.str();
}
