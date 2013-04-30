#ifndef KAMEK_H
#define KAMEK_H
#include "foreground.h"

class Kamek: public Foreground {
 public:
 /** Default constructor for witch */
 Kamek (QPixmap *pm, int nx, int ny);
 /** Animates witch */
 void move(int count); 
 /** Makes witch disappear when it hits other objects */
 void collideUp(int num);
 /** Makes witch disappear when it hits other objects */
 void collideDown(int num);
 /** Returns if witch is coasting or ready to throw a spike */
 bool spike;
};

/** Default constructor- kamek's y pos is randomly generated and set.
 *  It's z value is set to 2 and spike is set to false.
 *
 *  @param pointer to QPixmap
 *  @param x position
 *  @param y position 
 *  @return nothing
 */
Kamek::Kamek( QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 srand(time(NULL));
 int ax = rand()%10;
 srand(ax);
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
}

/** Moves witch back 2 pixels when a duration has elapsed and
 *  it isn't ready to throw a spike. If it is the image is
 *  change to be doing that and it's state is changed.
 *
 * @param count of how much time has elapsed since start of game
 * @return nothing
 */
void Kamek::move(int count) {
if(count%2 == 0){
 if(pos().x() > 16){
  moveBy(-2, 0);
 }
 else if(spike == false){
  state = 1;
  spike = true;
  setPixmap(qApp->applicationDirPath()+"/Pictures/Kamek2.png");
 }
}
}

/** If object collides with witch and witch is above object this function is called
 *  If the case isn't special the witch will disappear.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void Kamek::collideUp(int num){
 if(num == 0){
  setVisible(false);
 }
}

/** If object collides with witch and witch is below object this function is called
 *  If the case isn't special the witch will disappear.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void Kamek::collideDown(int num){
 if(num == 0){
  setVisible(false);
 }
}

#endif // KAMEK_H

