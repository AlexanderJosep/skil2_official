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
    return NULL;
}

void Entity::setID(int id) {
    this -> id = id;
}

void Entity::updateString(ostringstream &o, string data, int &priorLength, int columnSize) {
    if(o.tellp() > 0 && priorLength < 30) {
        o << setw(columnSize - (priorLength - data.length()));
    }
    o << data;
    priorLength = data.length();
}
