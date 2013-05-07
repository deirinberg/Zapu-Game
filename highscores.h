#ifndef HIGHSCORES_H
#define HIGHSCORES_H
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class HighScores {
 public:
 HighScores();
 void update(string name, int score);
 private:
 vector<string> names;
 vector<int> scores;
};

#endif // HIGHSCORES_H

