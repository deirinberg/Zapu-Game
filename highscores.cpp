#include "highscores.h"
#include <iomanip>
#include <sstream>

HighScores::HighScores(){
 ifstream fin;
 ofstream fout;
 fin.open("HSList.txt");
 if(!fin.fail()){
  string line;
  int score, num;
  getline(fin, line);
   while(!fin.eof()){
    getline(fin, line);
    stringstream ss(line);
    ss>>num;
    getline(ss, line, ' ');
    if(num < 10){
    getline(ss, line, ' ');
    }
    getline(ss, line, ' ');
    names.push_back(line);
    ss>>score;
    scores.push_back(score);
   }
 }
 fin.close();
}

void HighScores::update(string name, int score){
  if(scores.size() == 0 || score < scores.at(scores.size()-1)){
   names.push_back(name);
   scores.push_back(score);
  }
  else{
   for(unsigned int i = 0; i<scores.size(); i++){
    if(score > scores.at(i)){
     names.insert(names.begin()+i, name);
     scores.insert(scores.begin()+i, score);
     break;
    }
   }
  }
  ofstream fout;
  fout.open("HSList.txt");
  fout<<"Zapu High Scores";
  while(names.size() > 15){
   names.pop_back();
   scores.pop_back();
  }
  for(unsigned int j = 0; j<names.size(); j++){
   if(j<=8){
   fout<<endl<<left<<j+1<<".  "<<setw(12)<<names.at(j)<<" "<<scores.at(j);
   }
   else{
   fout<<endl<<left<<j+1<<". "<<setw(12)<<names.at(j)<<" "<<scores.at(j);
   }
  }
}
