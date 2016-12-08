#ifndef COMPUTERMANAGER_H
#define COMPUTERMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <string.h>
#include "computer.h"
#include "console.h"
#include "storage.h"

using namespace std;

class ComputerManager {
public:
    ComputerManager();
    void add(Console &c); // adds a new computer to the list
};

#endif // COMPUTERMANAGER_H

