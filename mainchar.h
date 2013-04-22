#ifndef MAINCHAR_H
#define MAINCHAR_H
#include "object.h"

class MainChar: public Object {
 public:
 MainChar (QPixmap *pm, int nx, int ny);
 void move(int count); // Implement the move method
 void keySignal(QKeyEvent *e);
 void keyRelease(QKeyEvent *r);
 void walk();
 void crouch();
 void jump();
 int num;
 double time;
 double dy;
 bool walking;
 bool jumping;
 bool egg;
};

MainChar::MainChar(QPixmap *pm, int nx, int ny ) : Object( pm, nx, ny ) {
num = 0;
//Any specific initialization code for BigThing goes here.
}
void MainChar::move(int count) {
if(count%40 == 0){
 if(walking == true){
  egg = false;
  jumping = false;
  walk();
 }
 else if(egg == true && num <=2){
  crouch();
 }
}
if(count%4 == 0){
 if(jumping == true){
  jump();
 }
}
}

void MainChar::keySignal(QKeyEvent *e){
 switch(e->key()){
   case Qt::Key_Up:
      cout<<"UP KEY\n";
      if(walking == true && jumping == false){
       walking = false;
       jumping = true;
       dy = 0;
       time = 0;
       num = 0;
      }
       break;
   case Qt::Key_Right:
      cout<<"RIGHT KEY\n";
      break;
   case Qt::Key_Down:
      cout<<"DOWN KEY\n";
      if(walking == true && egg == false){
        walking = false;
        egg = true;
        num = 0;
       }
       break;
   case Qt::Key_Left:
      cout<<"LEFT KEY\n"; 
      break;
   case Qt::Key_Space:
     cout<<"SPACE KEY\n";
     break;
  }
}

void MainChar::keyRelease(QKeyEvent *e){
 switch(e->key()){
   case Qt::Key_Up:
       break;
   case Qt::Key_Right:
      break;
   case Qt::Key_Down:
      cout<<"RELEASE DOWN KEY\n";
      if(egg == true){
        egg = false;
        walking = true;
        num = 0;
       }
       break;
   case Qt::Key_Left:
      cout<<"LEFT KEY\n"; 
      break;
   case Qt::Key_Space:
     cout<<"SPACE KEY\n";
     break;
  }
}

void MainChar::crouch(){
 QPixmap *pm = new QPixmap("/home/cs102/game_eirinber/Pictures/Egg2.png");
 setPixmap(*pm);
}

void MainChar::jump(){
  QPixmap *pm;
  float yi = 50*time + -5*time*time;
  time += .1;
  float yf = 50*time + -5*time*time;
  if(dy == 0){
   pm = new QPixmap("/home/cs102/game_eirinber/Pictures/Jump1.png");
   dy = yi - yf;
  }
  else if((yi-yf)>0){
   pm = new QPixmap("/home/cs102/game_eirinber/Pictures/Jump3.png");
  }
  else{
   pm = new QPixmap("/home/cs102/game_eirinber/Pictures/Jump2.png");
  }
 if((yi-yf)!= -dy){
  moveBy(0, yi-yf);
  }
  else{
   moveBy(0, yi-yf);
   jumping = false;
   walking = true;
  }
  setPixmap(*pm);
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
