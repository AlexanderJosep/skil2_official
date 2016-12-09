#ifndef CONFIG_H
#define CONFIG_H

#include <string>

using namespace std;

namespace config {
    /* Snake Configuration */
    const long SNAKE_SLEEP_TIME = 100;
    const int SNAKE_CELL_SIZE = 24;
    const int SNAKE_BAR_OFFSET = 150;
    const string SNAKE_DEFAULT_STATUS = "Press any key to begin!";

    /* Entity Configuration */
    const int PERSON = 0;
    const int COMPUTER = 1;
    const int NUMBER_OF_MACHINES_TYPES = 4;
    const string MACHINE_TYPES[NUMBER_OF_MACHINES_TYPES] =  {"Mechanic", "Electronic", "Transistor", "Quantum"};

    /* Commands and organization */
    const int COMMANDS_LENGTH = 18;
    const int INSTRUCTIONS_LENGTH = 9;
    const int DISPLAY_PERSON_INSTRUCTIONS_LENGTH = 5;
    const int DISPLAY_COMPUTER_INSTRUCTIONS_LENGTH = 4;
    const char COMMANDS[COMMANDS_LENGTH] = {'d', 's', 'a', 'i', 'q', 'c', 'e', 'r', 'g', // Instructions
                               'o', 'n', 'g', 'b', 'd', // Organization persons
                               'o', 'n', 'y', 't'}; // Organization computers
    const string INSTRUCTIONS[INSTRUCTIONS_LENGTH] = {"Use 'a' to add computer or person to the list.", "Use 'c' to clear the console.",
                                    "Use 'd' to display a list.", "Use 'e' to edit a list.", "Use 'g' to start a game of snake.",
                                    "Use 'r' to remove from a list.", "Use 's' to search.", "Use 'q' if you want to quit."};
    const string DISPLAY_PERSON_INSTRUCTIONS[DISPLAY_PERSON_INSTRUCTIONS_LENGTH] = {"Use 'b' to organize by birth year.",
                                    "Use 'd' to organize by death year.", "Use 'g' to organize by gender.",
                                    "Use 'n' to organize by names in alphabetical order.",
                                    "Use 'o' to have no organization."};
    const string DISPLAY_COMPUTER_INSTRUCTIONS[DISPLAY_COMPUTER_INSTRUCTIONS_LENGTH] = {"Use 'n' to organize by names in alphabetical order.",
                                    "Use 'y' to organize by year it was built.", "Use 't' to organize by type.", "Use 'o' to have no organization."};
}

#endif // CONFIG_H

