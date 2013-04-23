#ifndef GROUND_H
#define GROUND_H
#include "object.h"
#include "mainchar.h"

class Ground: public Object {
 public:
 Ground (QPixmap *pm, int nx, int ny);
 void move(int count); // Implement the move method
 void setInitial();
 void newImage(int max);
 void keySignal(QKeyEvent *e);
 void keyRelease(QKeyEvent *r);
 void getVx();
 bool continuous;
};

Ground::Ground( QPixmap *pm, int nx, int ny ) : Object( pm, nx, ny ) {
 cout<<"NEW GROUND"<<endl;
if(nx < 700){
 newImage(12);
 }
else{
 newImage(18);
}
}
void Ground::move(int count) {
 if(count%4 == 0){
 moveBy(-1, 0);
 }
}

void Ground::newImage(int max){
 QPixmap *p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground1.png");
 srand(time(NULL));
 int pic = rand()%max;
 cout<<pic<<endl;
 /*if(continuous == false){
  cout<<"CAUSE? "<<pos().x()<<endl;
  p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground16.png"); 
  continuous = false;
 }*/
// else{
  switch(pic){
  case 0: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground2.png"); break;
  case 1: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground3.png"); break;
  case 2: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground4.png"); break;
  case 3: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground5.png"); break;
  case 4: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground6.png"); break;
  case 5: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground7.png"); break;
  case 6: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground8.png"); break;
  case 7: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground9.png"); break;
  case 8: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground10.png"); break;
  case 9: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground11.png"); break;
  case 10: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground12.png"); break;
  case 11: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground13.png"); break;
  case 12: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground14.png"); break;
  default: p = new QPixmap("/home/cs102/game_eirinber/Pictures/Ground15.png"); 
    if(pos().y() == 20){
    setPos(pos().x()+96, pos().y()-21);
    y -= 21;
    }
    else{
    setPos(pos().x()+96, pos().y()+21);
    y+=21;
    }
    break;
  }
// }
 setPixmap(*p);
}

void Ground::keySignal(QKeyEvent *e){
  e->ignore();
}

void Ground::keyRelease(QKeyEvent *r){
  r->ignore();
}

#endif // BACKGROUND_H
