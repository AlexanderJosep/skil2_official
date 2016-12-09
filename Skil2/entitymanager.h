#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include "config.h"
#include "console.h"
#include "storage.h"
#include "person.h"
#include "computer.h"

using namespace config;

class EntityManager {
public:
    EntityManager(int currentYear);
    void end(); // tell storage to close it's connection with the sql database
    void add(Console &c, int type);
    void edit(Console &c, vector<Entity*> entities, int type); // edits a entity in a list
    void remove(Console &c, vector<Entity*> entities, int type); // remove a entity from a list
    vector<Entity*> getOrganizedEntities(int o, int type); // gets organized entity list which organizes by type o
    vector<Entity*> getSearchResults(Console &c, int type); // gets a search input and find the results according to that
private:
    short getListIndex(Console &c, int type); // select a index from a list
    short getRealIndex(vector<Entity*> entities, int index, int type); // get the actual index ; the old one was organized in some way
    string getName(Console &c, bool n, int type); // gets the name from user input, n is true if user is creating a new person, false if editing
    short getGender(Console &c, bool n); // gets the gender from user input, n is true if user is creating a new person, false if editing
    short getYear(Console &c, string s); // gets a year from user input
    short getDeathYear(Console &c, bool n, int birthYear); // gets the death year from user input, n is true if user is creating a new person, false if editing
    short getComputerType(Console &c, string s); // gets a computer type from user input
    short getYearBuilt(Console &c, bool n);
    bool validName(string name, int type); // checks if a name is valid or not
    string trim(string s); // trims the edges of a string for any pesky spaces
    string capitialize(string s); // capitalizes a string
    string toLowerCase(string s); // lowercases a string
    vector<Person> persons;
    vector<Computer> computers;
    Storage storage;
    int currentYear;
};

#endif // ENTITYMANAGER_H
