#ifndef STORAGE_H
#define STORAGE_H

#include <string.h>
#include <vector>
#include <fstream>
#include <QtSql>
#include "person.h"
#include "computer.h"
#include "console.h"
#include "connection.h"
#include "snakescore.h"

using namespace std;

class Storage {
public:
    Storage();
    Storage(string dbName);
    vector<Person> getPersons(); // loads persons from an sql database and returns them in a vector
    vector<Computer> getComputers(); // loads computers from an sql database and returns them in a vector
    vector<Connection> getConnections(); // loads connections from an sql database and returns them in a vector
    vector<SnakeScore> getSnakeScores(int grid); // loads hiscores from an sql database and returns them in a vector
    bool savePerson(Person &person); // saves a person to a sql database
    bool saveComputer(Computer &computer); // saves a computer to a sql database
    bool editPerson(Person &person, string name, short gender, short birthYear, short deathYear); // edits a person in a sql database
    bool editComputer(Computer &computer, string name, short birthYear, short type); // edits a computer in a sql database
    bool removePerson(Person &person); // removes a person from a sql database
    bool removeComputer(Computer &computer); // removes a computer from a sql database
    bool addConnection(Connection &connection); // adds a connection between a computer and a person
    bool removeConnection(Connection &connection); // removes a connection between a computer and a person
    bool addSnakeScore(string name, int score, int gridSize); // adds a snake score to a sql database; returns true if score updated
    void close(); // closes a connection with sql databases

private:
    string dbName;
    QSqlDatabase database;
};

#endif // STORAGE_H
