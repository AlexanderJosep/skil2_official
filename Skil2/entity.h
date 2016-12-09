#ifndef ENTITY_H
#define ENTITY_H

#include <sstream>
#include <iomanip>
#include <string>
#include "config.h"

using namespace config;

class Entity {
public:
    Entity();
    string getName();
    int getID();
    void setID(int id);
    virtual string getOutput() ; // gets output ready to be printed to the console
    void updateString(ostringstream &o, string data, int &priorLength, int columnSize); // helps with getting ouput string for console
protected:
    string name;
    int id;
};

#endif // ENTITY_H
