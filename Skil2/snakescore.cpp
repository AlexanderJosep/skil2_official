#include "snakescore.h"

SnakeScore::SnakeScore(string name, int score, int grid) {
    this -> name = name;
    this -> score = score;
    this -> grid = grid;
}

string SnakeScore::getName() {
    return name;
}

int SnakeScore::getScore() {
    return score;
}

int SnakeScore::getGridSize() {
    return grid;
}

void SnakeScore::setScore(int score) {
    this -> score = score;
}
