#include "entity.h"

Entity::Entity() {

}

string Entity::getName() {
    return name;
}

string Entity::getOutput() {
    return NULL;
}

void Entity::updateString(ostringstream &o, string data, int &priorLength, int columnSize) {
    if(o.tellp() > 0 && priorLength < 30) {
        o << setw(columnSize - (priorLength - data.length()));
    }
    o << data;
    priorLength = data.length();
}
