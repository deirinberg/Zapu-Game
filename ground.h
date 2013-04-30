#ifndef GROUND_H
#define GROUND_H
#include "object.h"
#include "background.h"

class Ground: public Background {
 public:
 /** Default constructor for foreground object */
 Ground (QPixmap *pm, int nx, int ny);
 /** Animates ground items */
 void move(int count); 
 /** Sets the amount of gaps in the ground */
 void setLimit(int num);
 /** Generates a new random image based on the limit */
 void newImage(int max);
};

/** Default constructor, inherits from background class but no new
 *  implementation necessary
 *
 *  @param pointer to QPixmap
 *  @param x position
 *  @param y position 
 *  @return nothing
 */
Ground::Ground( QPixmap *pm, int nx, int ny ) : Background( pm, nx, ny ) {

}
/** Moves ground objects over by two pixels after time has elapsed
 *
 *  @param count of how much time has elapsed since start of game
 *  @return nothing
 */
void Ground::move(int count) {
 if(count%3 == 0){
 moveBy(-2, 0);
 }
}
/** Calls newImage to be generated 
 *
 *  @param the amount of possible background images
 *  @return nothing
 */
void Ground::setLimit(int num){
  newImage(num);
}

/** Generates a random number based on the possible background images. 
 *  Cases 1-12 are normal while any others have gaps. The distance of the
 *  gaps are also based on the random number and so is the y coordinate
 *  floor level. setPos and setPixmap are called in the function
 *
 *  @param the amount of possible background images
 *  @return nothing
 */
void Ground::newImage(int max){
 QPixmap *p = new QPixmap(qApp->applicationDirPath()+"/Pictures/Ground1.png");
 srand(time(NULL));
 int pic = rand()%max;

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
