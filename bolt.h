#ifndef BOLT_H
#define BOLT_H
#include "foreground.h"

class Bolt: public Foreground {
 public:
 /** Default constructor */
 Bolt(QPixmap *pm, int nx, int ny);
 /** Animates bolts */
 void move(int count); 
 /** Makes bolt disappear when hits other objects */
 void collideUp(int num);
 /** Makes bolt disappear when hits other objects */
 void collideDown(int num);
};

/** Default constructor- sets zValue to be above ground objects in view
 *
 *  @param pointer to QPixmap
 *  @param x position
 *  @param y position 
 *  @return nothing
 */
Bolt::Bolt( QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 setZValue(1);
}

/** Moves bolt forward 2 pixels back when a duration has elapsed
 *
 * @param count of how much time has elapsed since start of game
 * @return nothing
 */
void Bolt::move(int count) {
if(count%2 == 0){
 moveBy(2, 0);
}
}

/** If object collides with bolt and bolt is above object this function is called
 *  If the case isn't special the bolt will disappear.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void Bolt::collideUp(int num){
 if(num!=-1){
  setVisible(false);
 }
}

/** If object collides with bolt and bolt is below object this function is called
 *  If the case isn't special the bolt will disappear.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void Bolt::collideDown(int num){
 if(num!=-1){
  setVisible(false);
 }
}


#endif // BULLET_H
