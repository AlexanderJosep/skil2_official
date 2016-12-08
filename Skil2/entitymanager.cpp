#include "entitymanager.h"

EntityManager::EntityManager(int currentYear) {
    this -> currentYear = currentYear;
    this -> persons = storage.getPersons();
}

void EntityManager::add(Console &c, int type) {
    string name = getName(c, true);
    if(type == PERSON) {
        short gender = getGender(c, true);
        short birthYear = getYear(c, "Birth year");
        short deathYear = getDeathYear(c, true, birthYear);
        Person person = Person(name, gender, birthYear, deathYear);
        if(storage.savePerson(person)) {
            persons.push_back(person);
            c.println("You have added "+name+" to the persons list.");
        } else {
            c.println("Failed to add "+name+" to the persons list.");
        }
    } else {
        short type = getComputerType(c, "ID of computer type");
        short yearBuilt = getYearBuilt(c, true);
        Computer computer = Computer(name, type, yearBuilt);
        computers.push_back(computer);
        c.println("You have added "+name+" to the computers list.");
    }
    c.newLine();
}

void EntityManager::edit(Console &c, vector<Person> pList) {
    short index = getRealIndex(pList, getListIndex(c));
    string oldName = persons[index].getName();
    c.println("Old name: "+oldName);
    string name = getName(c, false);
    short oldGender = persons[index].getGender() ;
    string oldGenderString = (oldGender == 0 ? "Male" : "Female");
    c.println("Old gender: "+oldGenderString);
    short gender = getGender(c, false);
    short oldBirthYear = persons[index].getBirthYear();
    c.println("Old birth year: "+to_string(oldBirthYear));
    short birthYear = getYear(c, "Year built");
    short oldDeathYear = persons[index].getDeathYear();
    if(oldDeathYear > 0) {
         c.println("Old death year: "+to_string(oldDeathYear));
    } else {
         c.println("Old person did not have a death year");
    }
    short deathYear = getDeathYear(c, false, birthYear);
    if(storage.editPerson(persons[index], oldName, oldGender, oldBirthYear, oldDeathYear)) {
        persons[index].setData(name, gender, birthYear, deathYear);
        c.println("You have edited "+name+" (old name: "+oldName+").");
    } else {
        c.println("You failed to edit "+name+" (old name: "+oldName+").");
    }
}

void EntityManager::remove(Console &c, vector<Person> pList) {
    short index = getRealIndex(pList, getListIndex(c));
    string name = persons[index].getName();
    if(c.getBool("Are you sure you want to delete "+name, 'y', 'n')) {
        if(storage.removePerson(persons[index])) {
            persons.erase(persons.begin() + index);
            c.println("You have deleted "+name+".");
        } else {
            c.println("Failed to delete "+name+".");
        }
    } else {
        c.println("Cancelled.");
    }
}

short EntityManager::getRealIndex(vector<Person> pList, int index) {
    for(unsigned int i = 0; i < persons.size(); i++) {
        if(persons[i].getName() == pList[index - 1].getName() && persons[i].getGender() == pList[index - 1].getGender()
                && persons[i].getBirthYear() == pList[index - 1].getBirthYear() && persons[i].getDeathYear() == pList[index - 1].getDeathYear()) {
            index = i;
            break;
        }
    }
    return index;
}

short EntityManager::getListIndex(Console &c) {
    short index;
    while (true){
        index = c.getShort("Select index from the list (1-"+to_string(persons.size())+")");
        if(index > 0 && index <= (signed) persons.size()) {
            break;
        }
        c.println("Invalid index!");
        c.clearBuffer();
    }
    return index;
}

string EntityManager::getName(Console &c, bool n) {
    string s = n ? "Name" : "New name";
    string name = c.getString(s, true);
    while(true) {
        name = trim(name);
        if(validName(name)) {
           name = capitialize(name);
           break;
        } else {
            c.println("Invalid name!");
            name = c.getString(s, false);
        }
    }
    return name;
}

short EntityManager::getGender(Console &c, bool n) {
    string s = n ? "Gender" : "New gender";
    short gender;
    while(true) {
        char g = c.getChar(s + " (m/f)");
        if(g == 'm' || g == 'f') {
            gender = (g == 'm' ? 0 : 1);
            break;
        }
        c.println("Invalid gender!");
        c.clearBuffer();
    }
    return gender;
}

short EntityManager::getYear(Console &c, string s) {
    short year;
    while (true){
        year = c.getShort(s);
        if(year > 0 && year <= currentYear) { // disallow future years and years 0 + b.c.
            break;
        }
        c.println("Invalid year!");
        c.clearBuffer();
    }
    return year;
}

short EntityManager::getDeathYear(Console &c, bool n, int birthYear) {
    short deathYear = -1;
    if(c.getBool("Person dead", 'y', 'n')) {
        while(true) {
            string s = n ? "Death year" : "New death year";
            deathYear = c.getShort(s);
            if(deathYear >= birthYear && deathYear <= currentYear) {
                break;
            }
            c.println("Please choose a death year the same or after the birth year.");
            c.clearBuffer();
        }
    }
    return deathYear;
}

short EntityManager::getComputerType(Console &c, string s) {
    short type;
    while (true){
        // print out all computer types
        c.print("Computer types (ID in parenthesis): ");
        for(int i = 0; i < NUMBER_OF_MACHINES_TYPES; i++) {
            c.print(MACHINE_TYPES[i]+" ("+to_string(i + 1)+")");
            if(i + 1 >= NUMBER_OF_MACHINES_TYPES) {
                c.newLine();
            } else if(i + 2 < NUMBER_OF_MACHINES_TYPES) {
                c.print(", ");
            } else {
                c.print("and ");
            }
        }
        type = c.getShort(s);
        if(type > 0 && type <= NUMBER_OF_MACHINES_TYPES) {
            break;
        }
        c.println("Invalid type!");
        c.clearBuffer();
    }
    return type - 1;
}

short EntityManager::getYearBuilt(Console &c, bool n) {
    short yearBuilt = -1;
    if(c.getBool("Was the computer built", 'y', 'n')) {
        while(true) {
            string s = n ? "Year built" : "New year built";
            yearBuilt = c.getShort(s);
            if(yearBuilt > 0 && yearBuilt <= currentYear) { // disallow future years and years 0 + b.c.
                break;
            }
            c.println("Please choose a valid year.");
            c.clearBuffer();
        }
    }
    return yearBuilt;
}

vector<Entity*> EntityManager::getOrganizedEntities(int o, int type) {
    vector<Entity*> out;
    if(o == 0 && type == PERSON) {
        for(unsigned int i = 0; i < persons.size(); i++) {
            out.push_back(&persons[i]);
        }
    }
    if(o == 0 && type == COMPUTER) {
        for(unsigned int i = 0; i < computers.size(); i++) {
            out.push_back(&computers[i]);
        }
    }
    if(o == 1) { // organize by names alphabetically
        vector<string> names;
        if(type == PERSON) {
            for(unsigned int i = 0; i < persons.size(); i++) {
                names.push_back(persons[i].getName());
            }
        } else {
            for(unsigned int i = 0; i < computers.size(); i++) {
                names.push_back(computers[i].getName());
            }
        }
        sort(names.begin(), names.end());
        for(unsigned int i = 0; i < names.size(); i++) {
            if(type == PERSON) {
                for(unsigned int j = 0; j < persons.size(); j++) {
                    if(names[i] == persons[j].getName()) {
                        out.push_back(&persons[j]);
                        break;
                    }
                }
            } else {
                for(unsigned int j = 0; j < computers.size(); j++) {
                    if(names[i] == computers[j].getName()) {
                        out.push_back(&computers[j]);
                        break;
                    }
                }
            }
        }
    }
    if(o == 2 && type == PERSON) { // organize by gender
        for(int j = 0; j < 2; j++) {
            for(unsigned int i = 0; i < persons.size(); i++) {
                if(persons[i].getGender() == j) {
                    out.push_back(&persons[i]);
                }
            }
        }
    }
    if(((o == 3 || o == 4) && type == PERSON) || (o == 2 && type == COMPUTER)) { // organize by birth year or by death year or by built year
        vector<int> years;
        vector<Person> copyPersons;
        vector<Computer> copyComputers;
        if(type == PERSON) {
            for(unsigned int i = 0; i < persons.size(); i++) {
                if((o == 3 && persons[i].getBirthYear() >= 0) || (o == 4 && persons[i].getDeathYear() >= 0)) {
                    years.push_back(o == 3 ? persons[i].getBirthYear() : persons[i].getDeathYear());
                }
            }
        } else {
            for(unsigned int i = 0; i < computers.size(); i++) {
                if(computers[i].getYear() >= 0) {
                    years.push_back(computers[i].getYear());
                }
            }
        }
        sort(years.begin(), years.end());
        if(type == PERSON) {
            for(unsigned int i = 0; i < persons.size(); i++) {
                copyPersons.push_back(persons[i]);
            }
        } else {
            for(unsigned int i = 0; i < computers.size(); i++) {
                copyComputers.push_back(computers[i]);
            }
        }

        for(unsigned int i = 0; i < years.size(); i++) {
            if(type == PERSON) {
                for(unsigned int j = 0; j < copyPersons.size(); j++) {
                    if((o == 3 && years[i] == copyPersons[j].getBirthYear()) || (o == 4 && years[i] == copyPersons[j].getDeathYear())) {
                        out.push_back(&copyPersons[j]);
                        copyPersons.erase(copyPersons.begin() + j);
                        break;
                    }
                }
            } else {
                for(unsigned int j = 0; j < copyComputers.size(); j++) {
                    if(years[i] == copyComputers[j].getYear()) {
                        out.push_back(&copyComputers[j]);
                        copyComputers.erase(copyComputers.begin() + j);
                        break;
                    }
                }
            }
        }
        if(o == 4) {
            for(unsigned int j = 0; j < copyPersons.size(); j++) {
                 out.push_back(&copyPersons[j]);
            }
        }
        if(type == COMPUTER) {
            for(unsigned int j = 0; j < copyComputers.size(); j++) {
                 out.push_back(&copyComputers[j]);
            }
        }
    }
    if(o == 3 && type == COMPUTER) {
        for(int i = 0; i < NUMBER_OF_MACHINES_TYPES; i++) {
            for(unsigned int j = 0; j < computers.size(); j++) {
                if(computers[i].getName() == MACHINE_TYPES[i]) {
                    out.push_back(&computers[i]);
                }
            }
        }
    }
    return out;
}


bool EntityManager::validName(string name) {
    if(name.length() <= 0 || name.find("  ") != string::npos) {
        return false;
    }
    for(unsigned int i = 0; i < name.length(); i++) {
        if(!isalpha(name[i]) && name[i] != 32) {
            return false;
        }
    }
    return true;
}

string EntityManager::trim(string s) {
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    return s;
}

string EntityManager::capitialize(string s) {
    s = toLowerCase(s);
    const char* c = s.c_str();
    bool capitalizeNext = true;
    char out[s.length() - 1];
    for(unsigned int i = 0; i <= s.length(); i++) {
        out[i] = *(c + i);
        if(capitalizeNext && out[i] != ' ') {
            capitalizeNext = false;
            out[i] -= 32;
        }
        if(out[i] == ' ') {
            capitalizeNext = true;
        }
    }
    return string(out);
}

string EntityManager::toLowerCase(string s) {
    string out;
    out.resize(s.size());
    transform(s.begin(), s.end(), out.begin(), ::tolower);
    return out;
}

vector<Person> EntityManager::getPersonSearchResults(Console &c) {
    string search = toLowerCase(c.getString("Search", true));
    vector<Person> out;
    string male = "male";
    string female = "female";
    for(Person p : persons) {
        if(toLowerCase(p.getName()).find(search) != string::npos || to_string(p.getBirthYear()).find(search) != string::npos
                || (p.getGender() == 0 && male.find(search) != string::npos) || (search != male && p.getGender() == 1 && female.find(search) != string::npos)
                || (p.getDeathYear() >= 0 && to_string(p.getDeathYear()).find(search) != string::npos)) {
           out.push_back(p);
        }
    }
    return out;
}

