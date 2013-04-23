#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "object.h"

class Background: public Object {
 public:
 Background (QPixmap *pm, int nx, int ny);
 void move(int count); // Implement the move method
 void setGround(int y);
 void keySignal(QKeyEvent *e);
 void keyRelease(QKeyEvent *r);
};

Background::Background( QPixmap *pm, int nx, int ny ) : Object( pm, nx, ny ) {
//Any specific initialization code for BigThing goes here.
}
void Background::move(int count) {
setPos(100, 100);
//Implement the movement behavior of BigThing here. This is required.
}

void Background::setGround(int y){
 
}

void Background::keySignal(QKeyEvent *e){
  delete e;
}

void Background::keyRelease(QKeyEvent *r){
  delete r;
}

#endif // BACKGROUND_H
