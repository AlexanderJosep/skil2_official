#include "console.h"
#include "entitymanager.h"
#include "snake.h"

Console::Console() {

}

void Console::addW(int w) {
    cout << setw(w);
}

void Console::print(string s) {
    cout << s;
}

void Console::println(string s) {
    cout << s << endl;
}

void Console::newLine() {
    cout << endl;
}

void Console::clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Console::printInstructions() {
    for(int i = 0; i < INSTRUCTIONS_LENGTH; i++) {
        println(INSTRUCTIONS[i]);
    }
}

void Console::printDisplayInstructions(int type) {
    if(type == PERSON) {
        for(int i = 0; i < DISPLAY_PERSON_INSTRUCTIONS_LENGTH; i++) {
            println(DISPLAY_PERSON_INSTRUCTIONS[i]);
        }
    } else {
        for(int i = 0; i < DISPLAY_COMPUTER_INSTRUCTIONS_LENGTH; i++) {
            println(DISPLAY_COMPUTER_INSTRUCTIONS[i]);
        }
    }
}

void Console::printColumns(bool includeIndex) {
    if(includeIndex) {
        print("      ");
    }
    print("Name");
    addW(30);
    print("Gender");
    addW(16);
    print("Birth year");
    addW(16);
    println("Death year");
    if(includeIndex) {
        print("      ");
    }
    for (int i = 0; i < 66; i++) {
        print("=");
    }
    newLine();
}

void Console::printEntities(vector<Entity*> entities, bool reverse, bool includeIndex) {
    if(entities.size() <= 0) {
        println("Nothing to display.");
        return;
    }
    newLine();
    printColumns(includeIndex);
    for(unsigned int i = (reverse ? entities.size() - 1 : 0); i < entities.size(); i += (reverse ? -1 : 1)) {
        if(includeIndex) {
            string s = to_string(i + 1);
            print(s);
            for(unsigned int j = 0; j < 6 - s.length(); j++) {
                print(" ");
            }
        }
        println(entities[i] -> getOutput());
    }
    newLine();
}

char Console::getChar(string s) {
    print(s + ": ");
    char c;
    cin >> c;
    return c;
}

short Console::getShort(string s) {
    print(s + ": ");
    short in;
    cin >> in;
    return in;
}

bool Console::getBool(string s, char y, char n) {
    char c;
    while(true) {
        clearBuffer();
        print(s + " ("+y+"/"+n+"): ");
        cin >> c;
        if(c == y || c == n) {
            break;
        }
        println("Invalid command!");
    }
    return c == y;
}

string Console::getString(string s, bool ignore) {
    string in;
    while(true) {
        if(ignore) {
            cin.ignore();
        }
        print(s + " (max 30 chars): ");
        getline(cin, in);
        if(in.length() <= 30) {
            break;
        }
        println("Please don't use more than 30 characters.");
        ignore = false;
    }
    return in;
}

//type = 0 checks for basic commands, type = 1 / 2 checks for display organization commands (1 = persons, 2 = computers)
int Console::getIndex(char c, int type) {
    for(int i = type * 9 - (type == 2 ? 4 : 0); i < (type == 0 ? 9 : ((type - 1) * 5 + 14)); i++) {
        if(c == COMMANDS[i]) {
            return i;
        }
    }
    return -1;
}

int Console::getInstruction(int type) {
    int i;
    while(true) {
        i = getIndex(getChar((type == 0 ? "Instruction" : "Organization")), type);
        if(i < 0) {
            println("Invalid command!");
            clearBuffer();
            continue;
        } else {
            break;
        }
    }
    return i - (type >= 1 ? ((type - 1) * 5 + 9) : 0);
}

void Console::process() {
    time_t t = time(NULL);
    tm* tPtr = localtime(&t);
    int currentYear = tPtr -> tm_year + 1900; // gets the year
    println("The year is "+to_string(currentYear)+" and you're on Earth.");

    EntityManager manager = EntityManager(currentYear);
    printInstructions();
    while(true) {
        int i = getInstruction(0);
        if(i == 0) { // display
            int type = !getBool("Persons or computers", 'p', 'c');
            printDisplayInstructions(type);
            int o = getInstruction(1 + type);
            bool rev = getBool("Reverse output", 'y', 'n');
            printEntities(manager.getOrganizedEntities(o, type), rev, false);
        }
        if(i == 1) { // search
            int type = !getBool("Persons or computers", 'p', 'c');
            printEntities(manager.getSearchResults(*this, type), false, false);
        }
        if(i == 2) { // add person
            manager.add(*this, !getBool("Person or computer", 'p', 'c'));
        }
        if(i == 3) { // info
            printInstructions();
        }
        if(i == 4) { // quit
            break;
        }
        if(i == 5) { // clear console
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }
        if(i == 6 || i == 7) {
            int type = !getBool("Persons or computers", 'p', 'c');
            vector<Entity*> entities = manager.getOrganizedEntities(1, type); // organized in alphabetical order
            printEntities(entities, false, true); // alphabetical organization
            if(i == 6) { // edit person
                manager.edit(*this, entities, type);
            } else { // remove person
                manager.remove(*this, entities, type);
            }
        }
        if(i == 8) { // snake
            Snake(*this);
        }
        if(i != 3 && i != 5) {
            println("Press 'i' for instructions.");
        }
    }
}
