#ifndef GROUND_H
#define GROUND_H
#include "object.h"

class Ground: public Object {
 public:
 Ground (QPixmap *pm, int nx, int ny);
 void move(); // Implement the move method
 void walk();
};

Ground::Ground( QPixmap *pm, int nx, int ny ) : Object( pm, nx, ny ) {
//Any specific initialization code for BigThing goes here.
}
void Ground::move() {
setPos(100, 100);
//Implement the movement behavior of BigThing here. This is required.
}
void Ground::walk(){

}

#endif // BACKGROUND_H
