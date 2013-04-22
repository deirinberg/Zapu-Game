#ifndef GROUND_H
#define GROUND_H
#include "object.h"

class Ground: public Object {
 public:
 Ground (QPixmap *pm, int nx, int ny);
 void move(int count); // Implement the move method
 void keySignal(QKeyEvent *e);
 void keyRelease(QKeyEvent *r);
};

Ground::Ground( QPixmap *pm, int nx, int ny ) : Object( pm, nx, ny ) {
//Any specific initialization code for BigThing goes here.
}
void Ground::move(int count) {
setPos(100, 100);
//Implement the movement behavior of BigThing here. This is required.
}

void Ground::keySignal(QKeyEvent *e){
  delete e;
}

void Ground::keyRelease(QKeyEvent *r){
  delete r;
}

#endif // BACKGROUND_H
