#ifndef STORAGE_H
#define STORAGE_H

#include <string.h>
#include <vector>
#include <fstream>
#include <QtSql>
#include "person.h"
#include "console.h"

using namespace std;

class Storage {
public:
    Storage();
    Storage(string dbName);
    vector<Person> getPersons(); // loads persons from an sql database
    bool savePerson(Person &person); // saves a person to a sql database
    bool editPerson(Person &person, string name, short gender, short birthYear, short deathYear); // edits a person in a sql database
    bool removePerson(Person &person); // removes a person from a sql database

private:
    string dbName;
    QSqlDatabase database;
};

#endif // STORAGE_H
