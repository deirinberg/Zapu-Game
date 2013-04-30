#ifndef BULLET_H
#define BULLET_H
#include "foreground.h"
#include <time.h>

class Bullet: public Foreground {
 public:
 Bullet (QPixmap *pm, int nx, int ny);
 void move(int count); // Implement the move method
 void sink();
 void collideUp(int num);
 void collideDown(int num);
 bool sinking;
};

Bullet::Bullet( QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 srand(time(NULL));
 int py = rand()%9;
 cout<<"PY: "<<py<<"\n";
 if(py<=2){
 py = -100;
 }
 else if(py<=5){
 py = -70;
 }
 else{
 py = -200;
 }
 state = 2;
 cout<<"Height: "<<py<<endl;
 setPos(768, py);
 setZValue(2);
 sinking = false;
//Any specific initialization code for BigThing goes here.
}
void Bullet::move(int count) {
if(count%2 == 0){
 if(sinking == false){
  moveBy(-2, 0);
 }
 else{
  moveBy(0, 2);
 }
}
//Implement the movement behavior of BigThing here. This is required.
}

void Bullet::collideUp(int num){
 //yoshi case
 if(num == 0){
 
 }
}

void Bullet::collideDown(int num){
//yoshi case
 if(num == 0){
   sinking = true;
 }
}

#endif // BULLET_H
