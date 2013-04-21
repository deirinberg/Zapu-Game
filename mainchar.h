#ifndef MAINCHAR_H
#define MAINCHAR_H
#include "object.h"

class MainChar: public Object {
 public:
 MainChar (QPixmap *pm, int nx, int ny);
 void move(); // Implement the move method
 int num;
 void walk();
};

MainChar::MainChar( QPixmap *pm, int nx, int ny ) : Object( pm, nx, ny ) {
num = 0;
//Any specific initialization code for BigThing goes here.
}
void MainChar::move() {
setPos(-100, -100);
//Implement the movement behavior of BigThing here. This is required.
}
//You may need other methods
void MainChar::walk(){
 QPixmap *pm = new QPixmap("/home/cs102/game_eirinber/Pictures/YW1.png");
 switch(num){
  case 1: pm = new QPixmap("/home/cs102/game_eirinber/Pictures/YW2.png"); break;
  case 2: pm = new QPixmap("/home/cs102/game_eirinber/Pictures/YW3.png"); break;
  case 3: pm = new QPixmap("/home/cs102/game_eirinber/Pictures/YW4.png"); break;
  case 4: pm = new QPixmap("/home/cs102/game_eirinber/Pictures/YW5.png"); break;
  case 5: pm = new QPixmap("/home/cs102/game_eirinber/Pictures/YW6.png"); break;
  case 6: pm = new QPixmap("/home/cs102/game_eirinber/Pictures/YW7.png"); break;
  case 7: pm = new QPixmap("/home/cs102/game_eirinber/Pictures/YW8.png"); break;
  }
  setPixmap(*pm);
  if(num <= 6){
   num++;
  }
  else{
   num = 0;
  }
}

#endif // MAINCHAR_H
