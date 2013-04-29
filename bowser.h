#ifndef BOWSER_H
#define BOWSER_H
#include "foreground.h"

class Bowser: public Foreground {
 public:
 Bowser(QPixmap *pm, int nx, int ny);
 void move(int count); // Implement the move method
 void collideUp(int num);
 void collideDown(int num);
 void walk(int count);
 bool shocked;
 int health;
};

Bowser::Bowser(QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 setPos(768, ny-75);
 setZValue(2);
 state = 3;
 health = 5;
}
void Bowser::move(int count) {
if(count%3 == 0){
 if(shocked == false/*&& pos().x()>30*/){
  moveBy(-1, 0);
 }
 else if(shocked == true){
  shocked = false;
 }
}
if(count%100 == 0 && health != 0){
 walk(count);
}
}

void Bowser::walk(int count){
 if(count%200 == 0){
  setPixmap(qApp->applicationDirPath()+"/Pictures/bWalk1.png");
 }
 else{
  setPixmap(qApp->applicationDirPath()+"/Pictures/bStand.png");
 }
}

void Bowser::collideUp(int num){
 if(num == 0){
  setVisible(false);
 }
}

void Bowser::collideDown(int num){
//shock case
 if(num == 3){
 cout<<"HEALTH: "<<health<<endl;
  if(health>0){
   setPixmap(qApp->applicationDirPath()+"/Pictures/bShock.png");
   shocked = true;
   health--;
   }
   else{
   setPixmap(qApp->applicationDirPath()+"/Pictures/bHurt.png");
   shocked = false;
   state = 4;
   }
 }
}

#endif // BOWSER_H
