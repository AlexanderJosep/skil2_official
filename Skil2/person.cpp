#include "person.h"

Person::Person(string name, short gender, short birthYear, short deathYear) {
    this -> name = name;
    this -> gender = gender;
    this -> birthYear = birthYear;
    this -> deathYear = deathYear;
}

short Person::getGender() {
    return gender;
}

short Person::getBirthYear() {
    return birthYear;
}

short Person::getDeathYear() {
    return deathYear;
}

void Person::setData(string name, short gender, short birthYear, short deathYear) {
    this -> name = name;
    this -> gender = gender;
    this -> birthYear = birthYear;
    this -> deathYear = deathYear;
}

//type: 0/1 = organize by name, 2 = organize by gender, 3 = organize by birth year, 4 = organize by death year
string Person::getOutput() {
    ostringstream out;
    string s = (gender == 0 ? "Male" : "Female");
    int priorLength  = 0;
    updateString(out, "" + name, priorLength, 0);
    updateString(out, "" + s, priorLength, 28);
    updateString(out, "" + to_string(birthYear), priorLength, 12);
    updateString(out, "" + (deathYear >= 0 ? to_string(deathYear) : "Not dead"), priorLength, 16);
    return out.str();
}
