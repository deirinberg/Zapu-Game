#ifndef GROUND_H
#define GROUND_H
#include "object.h"
#include "background.h"

class Ground: public Background {
 public:
 Ground (QPixmap *pm, int nx, int ny);
 void move(int count); // Implement the move method
 void setInitial();
 void setLimit(int num);
 void newImage(int max);
 void getVx();
 int limit;
 bool continuous;
};

Ground::Ground( QPixmap *pm, int nx, int ny ) : Background( pm, nx, ny ) {

}
void Ground::move(int count) {
 if(count%3 == 0){
 moveBy(-2, 0);
 }
}

void Ground::setLimit(int num){
  newImage(num);
}

void Ground::newImage(int max){
 QPixmap *p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground1.png");
 srand(time(NULL));
 int pic = rand()%max;
 cout<<pic<<endl;

  switch(pic){
  case 0: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground2.png"); break;
  case 1: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground3.png"); break;
  case 2: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground4.png"); break;
  case 3: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground5.png"); break;
  case 4: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground6.png"); break;
  case 5: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground7.png"); break;
  case 6: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground8.png"); break;
  case 7: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground9.png"); break;
  case 8: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground10.png"); break;
  case 9: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground11.png"); break;
  case 10: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground12.png"); break;
  case 11: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground13.png"); break;
  case 12: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground14.png"); break;
  default: p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground15.png"); 
    int shiftX = 128;
    if(pic%3 == 0){
     shiftX = 96;
    }
    else if(pic%3 ==1){
     shiftX = 128;
    }
    else {
     shiftX = 192;
    }
    if(pos().y() == 20){
     if(pic%2 == 1){
      setPos(pos().x()+shiftX, pos().y()-17);
     }
     else{
     setPos(pos().x()+shiftX, pos().y()-34);
     }
    }
    else if(pos().y() == 3){
     if(pic%2 == 1){
     setPos(pos().x()+shiftX, pos().y()+17);
     }
     else{
     setPos(pos().x()+shiftX, pos().y()-17);
     }
    }
    else if(pos().y() == -14){
     if(pic%2 == 1){
     setPos(pos().x()+shiftX, pos().y()+17);
     }
     else{
     setPos(pos().x()+shiftX, pos().y()+34);
     }
    }
    break;
  }
 setPixmap(*p);
}


#endif // BACKGROUND_H
