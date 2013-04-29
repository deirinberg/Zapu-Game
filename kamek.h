#ifndef KAMEK_H
#define KAMEK_H
#include "foreground.h"

class Kamek: public Foreground {
 public:
 Kamek (QPixmap *pm, int nx, int ny);
 void move(int count); // Implement the move method
 void sink();
 void setGround(int y);
 void keySignal(QKeyEvent *e);
 void keyRelease(QKeyEvent *r);
 void collideUp(int num);
 void collideDown(int num);
 bool spike;
};

Kamek::Kamek( QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 srand(time(NULL));
 int py = rand()%2;
 switch(py){
 case 0: py = -350; break;
 case 1: py = -280; break;
 }
 state = 0;
 spike = false;
 cout<<"PY: "<<py<<endl;
 setPos(768, py);
 setZValue(2);
//Any specific initialization code for BigThing goes here.
}
void Kamek::move(int count) {
if(count%2 == 0){
 if(pos().x() > 16){
  moveBy(-1, 0);
 }
 else if(spike == false){
  state = 1;
  spike = true;
  setPixmap(qApp->applicationDirPath()+"/Pictures/Kamek2.png");
 }
}
//Implement the movement behavior of BigThing here. This is required.
}

void Kamek::collideUp(int num){
 //yoshi case
 if(num == 0){
  setVisible(false);
 }
}

void Kamek::collideDown(int num){
//yoshi case
 if(num == 0){
  setVisible(false);
 }
}

#endif // KAMEK_H

