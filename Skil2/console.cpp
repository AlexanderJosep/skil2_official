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

void Console::ignoreNextClear() {
    ignoreClear = true;
}

void Console::clearBuffer() {
    if(!ignoreClear) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    ignoreClear = false;
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

void Console::printColumns(bool includeIndex, int type) {
    if(includeIndex) {
        print("      ");
    }
    print("Name");
    addW(type == PERSON ? 30 : 37);
    print(type == PERSON ? "Gender" : "Computer type");
    addW(16);
    print(type == PERSON ? "Birth year" : "Year built");
    if(type == PERSON) {
        addW(16);
        println("Death year");
    } else {
        newLine();
    }
    if(includeIndex) {
        print("      ");
    }
    for (int i = 0; i < (type == PERSON ? 66 : 57); i++) {
        print("=");
    }
    newLine();
}

void Console::printEntities(vector<Entity*> entities, bool reverse, bool includeIndex, int type) {
    if(entities.size() <= 0) {
        println("Nothing to display.");
        newLine();
        return;
    }
    newLine();
    printColumns(includeIndex, type);
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
    int ch = getchar();
    return ch;
}

short Console::getShort(string s) {
    short in;
    clearBuffer();
    while(true) {
        string str;
        print(s + ": ");
        getline(cin, str);
        bool accept = true;
        for(unsigned int i = 0; i < str.length(); i++) {
            if(!isdigit(str[i])) {
                accept = false;
                break;
            }
        }
        // this is to get rid of the possibility to give errors when hitting just enter.
        if(str.size() <= 0 || !accept) {
            println("Invalid input!");
            continue;
        }
        in = atoi(str.c_str());
        break;
    }
    ignoreNextClear();
    return in;
}

bool Console::getBool(string s, char y, char n) {
    int c = 0;
    while(true) {
        if(c != 10) {
            clearBuffer();
        }
        print(s + " ("+y+"/"+n+"): ");
        c = getchar();
        if(c == y || c == n) {
            break;
        }
        println("Invalid command!");
    }
    if (cin.fail()) {
       clearBuffer();
    }
    return c == y;
}

int Console::getOptionIndex(string s, char a, char b, char c) {
    int ch = 0;
    while(true) {
        if(c != 10) {
            clearBuffer();
        }
        print(s + " ("+a+"/"+b+"/"+c+"): ");
        ch = getchar();
        if(ch == a || ch == b || ch == c) {
            break;
        }
        println("Invalid command!");
    }
    if (cin.fail()) {
       clearBuffer();
    }
    return ch == a ? 0 : (ch == b ? 1 : 2);
}

string Console::getString(string s, bool ignore) {
    string in;
    while(true) {
        if(ignore) {
            clearBuffer();
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
    for(int i = type * 9 - (type == 2 ? 4 : 0); i < (type == 0 ? 9 : ((type - 1) * 4 + 14)); i++) {
        if(c == COMMANDS[i]) {
            return i;
        }
    }
    return -1;
}

int Console::getInstruction(int type) {
    int i;
    while(true) {
        char ch = getChar(type == 0 ? "Instruction" : "Organization");
        i = getIndex(ch, type);
        if(i < 0) {
            println("Invalid command!");
            if(ch != 10) {
                clearBuffer();
            }
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
            clearBuffer();
            int o = getInstruction(1 + type);
            bool rev = getBool("Reverse output", 'y', 'n');
            printEntities(manager.getOrganizedEntities(o, type), rev, false, type);
        }
        if(i == 1) { // search
            int type = !getBool("Persons or computers", 'p', 'c');
            printEntities(manager.getSearchResults(*this, type), false, false, type);
            ignoreNextClear();
        }
        if(i == 2) { // add person
            manager.add(*this, getOptionIndex("Person, computer or connection", 'p', 'c', 'o'));
        }
        if(i == 3) { // info
            printInstructions();
        }
        if(i == 4) { // quit
            manager.end();
            break;
        }
        if(i == 5) { // clear console
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            printInstructions();
        }
        if(i == 6 || i == 7) {
            int type = !getBool("Persons or computers", 'p', 'c');
            vector<Entity*> entities = manager.getOrganizedEntities(1, type); // organized in alphabetical order
            if(entities.size() > 0) {
                printEntities(entities, false, true, type);
            }
            if(i == 6) { // edit person
                if(entities.size() <= 0) {
                    println("Please add something to the list before editing.");
                    newLine();
                } else {
                    manager.edit(*this, entities, type);
                }
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
        clearBuffer();
    }
}
