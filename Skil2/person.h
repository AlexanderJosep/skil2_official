#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "entity.h"

using namespace std;

class Person : public Entity {
public:
    Person(string name, short gender, short birthYear, short deathYear);
    short getGender();
    short getBirthYear();
    short getDeathYear();
    void setData(string name, short gender, short birthYear, short deathYear); // set name, gender, birthYear and deathYear
    string getOutput(); // gets output ready to be printed to the console
private:
    short gender; // 0 male, 1 female
    short birthYear;
    short deathYear; // -1 if not dead
};

#endif // PERSON_H
