#include "connection.h"

Connection::Connection(int personID, int computerID) {
    this -> personID = personID;
    this -> computerID = computerID;
}

int Connection::getID() {
    return personID;
}

int Connection::getPersonID() {
    return personID;
}

int Connection::getComputerID() {
    return computerID;
}

void Connection::setID(int id) {
    this -> id = id;
}
