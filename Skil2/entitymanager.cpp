#include "entitymanager.h"

EntityManager::EntityManager(int currentYear) {
    this -> currentYear = currentYear;
    this -> persons = storage.getPersons();
    this -> computers = storage.getComputers();
    this -> connections = storage.getConnections();
    // set the person and computer pointer in connections
    // we're setting this to get a correct output when displaying connections in the console
    for(unsigned int i = 0; i < connections.size(); i++) {
       for(unsigned int j = 0; j < persons.size(); j++) {
            if(persons[j].getID() == connections[i].getPersonID()) {
                connections[i].setPerson(&persons[j]);
                break;
            }
        }
       for(unsigned int j = 0; j < computers.size(); j++) {
            if(computers[j].getID() == connections[i].getComputerID()) {
                connections[i].setComputer(&computers[j]);
                break;
            }
        }
    }
}

void EntityManager::end() {
    storage.close();
}

void EntityManager::add(Console &c, int type) {
    if(type == PERSON) {
        string name = getName(c, true, type);
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
    } else if(type == COMPUTER) {
        string name = getName(c, true, type);
        short type = getComputerType(c, "ID of computer type");
        short yearBuilt = getYearBuilt(c, true);
        Computer computer = Computer(name, yearBuilt, type);
        if(storage.saveComputer(computer)) {
            computers.push_back(computer);
            c.println("You have added "+name+" to the computers list.");
        } else {
            c.println("Failed to add "+name+" to the computers list.");
        }
    } else { // add a connection
        vector<Entity*> personsList = getOrganizedEntities(1, PERSON);
        vector<Entity*> computersList = getOrganizedEntities(1, COMPUTER);

        c.printEntities(personsList, false, true, PERSON);
        c.println("Person:");
        short personIndex = getRealIndex(personsList, getListIndex(c, PERSON), PERSON);

        c.printEntities(computersList, false, true, COMPUTER);
        c.println("Computer:");
        short computerIndex = getRealIndex(computersList, getListIndex(c, COMPUTER), COMPUTER);

        for(Connection connection : connections) {
            if(connection.getPersonID() == persons[personIndex].getID() && connection.getComputerID() == computers[computerIndex].getID()) {
                c.println("That connection has already been made.");
                c.newLine();
                return;
            }
        }
        Connection connection = Connection(persons[personIndex].getID(), computers[computerIndex].getID());
        connection.setPerson(&persons[personIndex]);
        connection.setComputer(&computers[computerIndex]);
        if(storage.addConnection(connection)) {
            connections.push_back(connection);
            c.println("Connected "+persons[personIndex].getName() +" and "+computers[computerIndex].getName()+" together.");
        } else {
            c.println("Failed to connect "+persons[personIndex].getName() +" and "+computers[computerIndex].getName()+" together.");
        }
    }
    c.newLine();
}

void EntityManager::edit(Console &c, vector<Entity*> entities, int type) {
    short index = getRealIndex(entities, getListIndex(c, type), type);
    string name;
    string oldName;
    if(type == PERSON) {
        oldName = persons[index].getName();
        c.println("Old name: "+oldName);
        name = getName(c, false, type);
        short oldGender = persons[index].getGender() ;
        string oldGenderString = (oldGender == 0 ? "Male" : "Female");
        c.println("Old gender: "+oldGenderString);
        short gender = getGender(c, false);
        short oldBirthYear = persons[index].getBirthYear();
        c.println("Old birth year: "+to_string(oldBirthYear));
        short birthYear = getYear(c, "Birth year");
        short oldDeathYear = persons[index].getDeathYear();
        if(oldDeathYear > 0) {
             c.println("Old death year: "+to_string(oldDeathYear));
        } else {
             c.println("Old person did not have a death year.");
        }
        short deathYear = getDeathYear(c, false, birthYear);
        Person person = Person(name, gender, birthYear, deathYear);
        if(storage.editPerson(person, oldName, oldGender, oldBirthYear, oldDeathYear)) {
            persons[index].setData(name, gender, birthYear, deathYear);
            c.println("You have edited "+name+" (old name: "+oldName+").");
        } else {
            c.println("You failed to edit "+name+" (old name: "+oldName+").");
        }
    } else {
        oldName = computers[index].getName();
        c.println("Old name: "+oldName);
        name = getName(c, false, type);
        short oldType = computers[index].getType();
        c.println("Old type is "+MACHINE_TYPES[oldType]+".");
        short type = getComputerType(c, "New ID of computer type");
        short oldYear = computers[index].getYear();
        if(oldYear < 0) {
            c.println("Old computer was not built");
        } else {
            c.println("Old year built: "+to_string(oldYear));
        }
        short yearBuilt = getYearBuilt(c, false);
        Computer computer = Computer(name, yearBuilt, type);
        if(storage.editComputer(computer, oldName, oldYear, oldType)) {
            computers[index].setData(name, yearBuilt, type);
            c.println("You have edited "+name+" (old name: "+oldName+").");
        } else {
            c.println("You failed to edit "+name+" (old name: "+oldName+").");
        }
    }
    c.newLine();
}

void EntityManager::remove(Console &c, vector<Entity*> entities, int type) {
    if(entities.size() <= 0) {
        c.println("Nothing to remove.");
        c.newLine();
        return;
    }
    short index = getListIndex(c, type);
    if(type != CONNECTION) { // the connection list hasn't been organized and doesn't need to be
        index = getRealIndex(entities, index, type); // get real non-organized index
    }
    string name;
    if(type == PERSON) {
        name = persons[index].getName();
    } else if(type == COMPUTER){
        name = computers[index].getName();
    } else {
        name = connections[index - 1].getName();
    }
    string addon = type == CONNECTION ? " the connection" : "";
    if(c.getBool("Are you sure you want to delete"+addon+" '"+name+"'", 'y', 'n')) {
        if(type == PERSON) {
            if(storage.removePerson(persons[index])) {
                persons.erase(persons.begin() + index);
                c.println("You have deleted "+name+".");
            } else {
                c.println("Failed to delete "+name+".");
            }
        } else if(type == COMPUTER) {
            if(storage.removeComputer(computers[index])) {
                computers.erase(computers.begin() + index);
                c.println("You have deleted "+name+".");
            } else {
                c.println("Failed to delete "+name+".");
            }
        } else {
            if(storage.removeConnection(connections[index - 1])) {
                connections.erase(connections.begin() + index - 1);
                c.println("You have deleted "+name+".");
            } else {
                c.println("Failed to delete "+name+".");
            }
        }
    } else {
        c.println("Cancelled.");
    }
    c.newLine();
}

short EntityManager::getRealIndex(vector<Entity*> entities, int index, int type) {
    if(type == PERSON) {
        for(unsigned int i = 0; i < persons.size(); i++) {
            if(persons[i].getName() == entities[index - 1] -> getName()) { // checks first for name before casting
                Person* person = static_cast<Person*>(entities[index - 1]);
                if(persons[i].getGender() == person -> getGender()
                        && persons[i].getBirthYear() == person -> getBirthYear() && persons[i].getDeathYear() == person -> getDeathYear()) {
                    index = i;
                    break;
                }
            }
        }
    } else {
        for(unsigned int i = 0; i < computers.size(); i++) {
            if(computers[i].getName() == entities[index - 1] -> getName()) { // checks first for name before casting
                Computer* computer = static_cast<Computer*>(entities[index - 1]);
                if(computers[i].getYear() == computer -> getYear() && computers[i].getType() == computer -> getType()) {
                    index = i;
                    break;
                }
            }
        }
    }
    return index;
}

short EntityManager::getListIndex(Console &c, int type) {
    short index;
    int listSize = type == PERSON ? persons.size() : (type == COMPUTER ? computers.size() : connections.size());
    while (true){
        index = c.getShort("Select index from the list (1-"+to_string(listSize)+")");
        if(index > 0 && index <= listSize) {
            break;
        }
        c.println("Invalid index!");
    }
    return index;
}

string EntityManager::getName(Console &c, bool n, int type) {
    string s = n ? "Name" : "New name";
    string name = c.getString(s, true);
    while(true) {
        name = trim(name);
        if(validName(name, type)) {
           if(type != COMPUTER) { // computers shouildn't have to be capitalized (IBM, BBC Micro & more)
                name = capitialize(name);
           }
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
        c.ignoreNextClear();
        char g = c.getBool(s, 'm', 'f');
        gender = (g == 'm' ? 0 : 1);
        break;
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
    }
    return year;
}

short EntityManager::getDeathYear(Console &c, bool n, int birthYear) {
    short deathYear = -1;
    if(c.getBool("Person dead", 'y', 'n')) {
        while(true) {
            string s = n ? "Death year" : "New death year";
            deathYear = c.getShort(s);
            if(deathYear >= birthYear && deathYear <= currentYear) { // disallow years before birth year and future years
                break;
            }
            c.println("Please choose a death year the same or after the birth year.");
        }
    }
    return deathYear;
}

short EntityManager::getComputerType(Console &c, string s) {
    short type;
    c.ignoreNextClear();
    while (true){
        // print out all computer types
        c.print("Computer types (ID in parenthesis): ");
        for(int i = 0; i < NUMBER_OF_MACHINES_TYPES; i++) {
            c.print(MACHINE_TYPES[i]+"("+to_string(i + 1)+")");
            if(i + 1 >= NUMBER_OF_MACHINES_TYPES) {
                c.newLine();
            } else if(i + 2 < NUMBER_OF_MACHINES_TYPES) {
                c.print(", ");
            } else {
                c.print(" and ");
            }
        }
        type = c.getShort(s);
        if(type > 0 && type <= NUMBER_OF_MACHINES_TYPES) {
            break;
        }
        c.println("Invalid type!");
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
        }
    }
    return yearBuilt;
}

vector<Entity*> EntityManager::getOrganizedEntities(int o, int type) {
    vector<Entity*> out;
    if(type == CONNECTION) {
        for(unsigned int i = 0; i < connections.size(); i++) {
            out.push_back(&connections[i]);
        }
    }
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
    if(o == 1 && type != CONNECTION) { // organize by names alphabetically
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
        sort(names.begin(), names.end()); // sort all the names alphabetically
        // then we link each name to a entity and add it to a list to get a sorted entity list
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
        vector<Person*> copyPersons;
        vector<Computer*> copyComputers;
        // we add all the years to a vector
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
        sort(years.begin(), years.end()); // sort the years, smallest years first
        if(type == PERSON) {
            for(unsigned int i = 0; i < persons.size(); i++) {
                copyPersons.push_back(&persons[i]);
            }
        } else {
            for(unsigned int i = 0; i < computers.size(); i++) {
                copyComputers.push_back(&computers[i]);
            }
        }
        // then we link each year to a entity and add it to a list to get a sorted entity list
        for(unsigned int i = 0; i < years.size(); i++) {
            if(type == PERSON) {
                for(unsigned int j = 0; j < copyPersons.size(); j++) {
                    if((o == 3 && years[i] == copyPersons[j] -> getBirthYear()) || (o == 4 && years[i] == copyPersons[j] -> getDeathYear())) {
                        out.push_back(copyPersons[j]);
                        copyPersons.erase(copyPersons.begin() + j);
                        break;
                    }
                }
            } else {
                for(unsigned int j = 0; j < copyComputers.size(); j++) {
                    if(years[i] == copyComputers[j] -> getYear()) {
                        out.push_back(copyComputers[j]);
                        copyComputers.erase(copyComputers.begin() + j);
                        break;
                    }
                }
            }
        }
        // then we add those who haven't been added to the return list
        if(o == 4) {
            for(unsigned int j = 0; j < copyPersons.size(); j++) {
                 out.push_back(copyPersons[j]);
            }
        }
        if(type == COMPUTER) {
            for(unsigned int j = 0; j < copyComputers.size(); j++) {
                 out.push_back(copyComputers[j]);
            }
        }
    }
    if(o == 3 && type == COMPUTER) {
        for(int i = 0; i < NUMBER_OF_MACHINES_TYPES; i++) {
            for(unsigned int j = 0; j < computers.size(); j++) {
                if(computers[j].getType() == i) { // check for the same type
                    out.push_back(&computers[j]);
                }
            }
        }
    }
    return out;
}


bool EntityManager::validName(string name, int type) {
    if(name.length() <= 0 || name.find("  ") != string::npos) {
        return false;
    }
    if(type == PERSON) { // computers should be able to have numbers and special chars as names
        for(unsigned int i = 0; i < name.length(); i++) {
            if(!isalpha(name[i]) && name[i] != 32) {
                return false;
            }
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
    s = toLowerCase(s); // lowercase everything first before we capitalize the first letter in a word
    const char* c = s.c_str();
    bool capitalizeNext = true;
    char out[s.length() - 1];
    for(unsigned int i = 0; i <= s.length(); i++) {
        out[i] = *(c + i);
        if(capitalizeNext && out[i] != ' ') {
            capitalizeNext = false;
            if(isalpha(out[i])) { // capitalize the char if it is actually a letter
                out[i] -= 32;
            }
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

vector<Entity*> EntityManager::getSearchResults(Console &c, int type) {
    if(type == PERSON) {
        c.println("You can search for 'male' or 'female' to get gender results.");
    } else if(type == COMPUTER) {
        c.println("You can search for 'built' or 'not built' to get specific results.");
    }
    string search = toLowerCase(c.getString("Search", true));
    vector<Entity*> out;
    if(type == PERSON) {
        string male = "male";
        string female = "female";
        for(unsigned int i = 0; i < persons.size(); i++) {
            if(toLowerCase(persons[i].getName()).find(search) != string::npos || to_string(persons[i].getBirthYear()).find(search) != string::npos
                    || (persons[i].getGender() == 0 && male.find(search) != string::npos) || (search != male && persons[i].getGender() == 1 && female.find(search) != string::npos)
                    || (persons[i].getDeathYear() >= 0 && to_string(persons[i].getDeathYear()).find(search) != string::npos)) {
               out.push_back(&persons[i]);
            }
        }
    }
    if(type == COMPUTER) {
        string built = "built";
        string notBuilt = "not built";
        for(unsigned int j = 0; j < computers.size(); j++) {
            bool added = false;
            for(int i = 0; i < NUMBER_OF_MACHINES_TYPES; i++) {
                if(computers[j].getType() == i) {
                    if(toLowerCase(MACHINE_TYPES[i]).find(search) != string::npos) {
                        out.push_back(&computers[j]);
                        added = true;
                    }
                    break;
                }
            }
            if(added) {
                continue;
            }
            if(toLowerCase(computers[j].getName()).find(search) != string::npos || (computers[j].getYear() && to_string(computers[j].getYear()).find(search) != string::npos)
                    || (computers[j].getYear() >= 0 && built.find(search) != string::npos) || (search != built && computers[j].getYear() < 0 && notBuilt.find(search) != string::npos)) {
               out.push_back(&computers[j]);
            }
        }
    }
    if(type == CONNECTION) {
        for(unsigned int j = 0; j < connections.size(); j++) {
            // search for either the person or the computer in a connection
            if(toLowerCase(connections[j].getPerson() -> getName()).find(search) != string::npos || toLowerCase(connections[j].getComputer() -> getName()).find(search) != string::npos) {
                out.push_back(&connections[j]);
            }
        }
    }
    return out;
}


void EntityManager::addSnakeScore(Console &c, int score, int grid) {
    string name = trim(c.getString("Hiscore name", true));
    if(storage.addSnakeScore(name, score, grid)) {
        c.println("New hiscore on '"+name+"': "+to_string(score));
    } else {
        c.println("Your score wasn't suffiecient enough for '"+name+"' to go on the hiscores.");
    }
    vector<SnakeScore> scores = storage.getSnakeScores(grid);
    vector<SnakeScore> topTenScores;
    for(int i = 0; i < 10; i++) {
        int idx = 0;
        if(scores.size() <= 0) {
            break;
        }
        for(unsigned int j = 1; j < scores.size(); j++) {
            if(scores[j].getScore() > scores[idx].getScore()) {
                idx = j;
            }
        }
        topTenScores.push_back(scores[idx]);
        scores.erase(scores.begin() + idx);
    }
    if(topTenScores.size() <= 0) {
        c.println("No scores to display.");
    } else {
        int size = topTenScores.size() > 10 ? 10 : topTenScores.size();
        c.println("Top "+to_string(size)+" players:");
        c.println("  \tName:\tScore");
        for(unsigned int i = 0; i < topTenScores.size(); i++) {
            c.println(to_string(i + 1) + ".\t"+topTenScores[i].getName()+"\t"+to_string(topTenScores[i].getScore()));
        }
    }
    c.newLine();
}
