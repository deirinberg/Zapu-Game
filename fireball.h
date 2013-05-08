#ifndef FIREBALL_H
#define FIREBALL_H
#include "foreground.h"

class FireBall: public Foreground {
 public:
 /** Default constructor */
 FireBall(QPixmap *pm, int nx, int ny);
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
FireBall::FireBall( QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 setZValue(2);
}

/** Moves fire ball backward 3 pixels back when a duration has elapsed
 *
 * @param count of how much time has elapsed since start of game
 * @return nothing
 */
void FireBall::move(int count) {
if(count%3 == 0){
 moveBy(-3, 0);
}
}

/** If object collides with bolt and bolt is above object this function is called
 *  If the case isn't special the bolt will disappear.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void FireBall::collideUp(int num){
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
void FireBall::collideDown(int num){
 if(num!=-1){
  setVisible(false);
 }
}


#endif // FIREBALL_H
