#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "object.h"

class Background: public Object {
 public:
 Background (QPixmap *pm, int nx, int ny);
 void move(); // Implement the move method
 void walk();
};

Background::Background( QPixmap *pm, int nx, int ny ) : Object( pm, nx, ny ) {
//Any specific initialization code for BigThing goes here.
}
void Background::move() {
setPos(100, 100);
//Implement the movement behavior of BigThing here. This is required.
}
void Background::walk(){

}

#endif // BACKGROUND_H
