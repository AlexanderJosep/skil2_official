#ifndef ENTITY_H
#define ENTITY_H

#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

class Entity {
public:
    Entity();
    string getName();
    virtual string getOutput() ; // gets output ready to be printed to the console
    void updateString(ostringstream &o, string data, int &priorLength, int columnSize); // helps with getting ouput string for console
protected:
    string name;
};

#endif // ENTITY_H
