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
  //  string b = (built == 0 ? "Not built" : "Built");
    int priorLength  = 0;
  //  updateString(out, "" + name, priorLength, 0);
  //  updateString(out, "" + b, priorLength, 28);
  //  updateString(out, "" + to_string(type), priorLength, 12);
   // if(built >= 0) {
   //     updateString(out, "" + to_string(built), priorLength, 16);
   // }
    return out.str();
}
