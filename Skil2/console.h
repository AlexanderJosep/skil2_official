#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include "config.h"
#include "person.h"
#include "entity.h"

using namespace config;

class Console  {
public:
    Console();
    void addW(int w); // prints setw(w) to the console
    void print(string s); // prints s to the console
    void println(string s); // prints s and \n to the console
    void newLine(); // prints \n to the console
    void printInstructions(); // prints all basic command instructions
    void printDisplayInstructions(int type); // prints all display organization instructions
    void printColumns(bool includeIndex, int type); // print all columns
    void printEntities(vector<Entity*> entities, bool reverse, bool includeIndex, int type); // print all entities in a list and reverses the output if reverse is true
    void ignoreNextClear();
    void clearBuffer(); // clears the stream buffer until it reaches \n
    char getChar(string s); // gets user input char
    short getShort(string s); // gets user input short
    bool getBool(string s, char y, char n); // gets user input bool (y/n)
    int getOptionIndex(string s, char a, char b, char c); // gets user input int (a=0,b=1,c=2)
    string getString(string s, bool ignore); // gets user input string and if ignore is true it ignores the first letter in the input buffer
    int getInstruction(int type); // gets the basic and organization command instruction
    void process(); // includes the main program loop
private:
    int getIndex(char c, int type); // gets the index of the basic/organization command
    bool ignoreClear;
};



#endif // CONSOLE_H
