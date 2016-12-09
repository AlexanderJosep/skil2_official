#ifndef SNAKESCORE_H
#define SNAKESCORE_H

#include <string>

using namespace std;

class SnakeScore {
public:
    SnakeScore(string name, int score, int grid);
    string getName();
    int getScore();
    int getGridSize();
    void setScore(int score);
private:
    string name;
    int score;
    int grid;
};

#endif // SNAKESCORE_H
