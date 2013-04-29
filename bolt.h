#ifndef BOLT_H
#define BOLT_H
#include "foreground.h"

class Bolt: public Foreground {
 public:
 Bolt(QPixmap *pm, int nx, int ny);
 void move(int count); // Implement the move method
 void collideUp(int num);
 void collideDown(int num);
};

Bolt::Bolt( QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {

//Any specific initialization code for BigThing goes here.
}
void Bolt::move(int count) {
//cout<<"BULLET POS: "<<pos().x()<<endl;
if(count%2 == 0){
 moveBy(1, 0);
}
//Implement the movement behavior of BigThing here. This is required.
}

void Bolt::collideUp(int num){

}

void Bolt::collideDown(int num){

}


#endif // BULLET_H
