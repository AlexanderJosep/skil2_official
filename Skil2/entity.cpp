#include "entity.h"

Entity::Entity() {

}

string Entity::getName() {
    return name;
}

int Entity::getID() {
    return id;
}

string Entity::getOutput() {
    return NULL; // should never be used
}

void Entity::setID(int id) {
    this -> id = id;
}

void Entity::updateString(ostringstream &o, string data, int &priorLength, int columnSize) {
    if(o.tellp() > 0 && priorLength < 30) {
        o << setw(columnSize - (priorLength - data.length())); // to keep the spacing correct we calculate the distance
    }
    o << data;
    priorLength = data.length();
}
