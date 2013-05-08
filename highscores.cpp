#include "highscores.h"
#include <iomanip>
#include <sstream>

/** Default constructor- Opens up "HSList.txt". If the file has already been created it will read in only
 *  the user name and score using a stringstream and then store them in the appropriate vectors. It will
 *  finally close the input text file.
 *
 *  @return nothing
 */
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

/** Updates the HSList.txt file after a user has lost. If there are no high scores or the user scored worse
 *  than other users it will be added to the end of each vector. If not the score will be sorted through
 *  the high scores list and inserted at the appropriate location. Finally an ofstream object will open
 *  up the "HSList.txt" file and rewrite it with a header "Zapu High scores". It will then remove the
 *  names/scores if there are more than 15 and write them all to the file. 
 *
 *  @param name of user that could potentially be added to the high scores
 *  @param int score that could potentially be added to high scores
 *  @return nothing
 */
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
