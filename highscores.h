#ifndef HIGHSCORES_H
#define HIGHSCORES_H
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class HighScores {
 public:
 /** Default constructor for high scores */
 HighScores();
 /** Update function for high scores when new name/score combo has been added */
 void update(string name, int score);
 private:
 /** A vector holding the names of the users with the high scores */
 vector<string> names;
 /** A vector holding the ints of the highest scores */
 vector<int> scores;
};

#endif // HIGHSCORES_H

