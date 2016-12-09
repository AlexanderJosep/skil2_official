#ifndef CONNECTION_H
#define CONNECTION_H

#include "entity.h"
#include "person.h"
#include "computer.h"

class Connection : public Entity {
public:
    Connection(int personID, int computerID);
    int getPersonID(); // get person id
    int getComputerID(); // get computer id
    string getName();
    void setPerson(Person *person);
    void setComputer(Computer *computer);
    Person* getPerson();
    Computer* getComputer();
    string getOutput(); // gets output ready to be printed to the console
private:
    int personID;
    int computerID;
    Person *person;
    Computer *computer;
};

#endif // CONNECTION_H
