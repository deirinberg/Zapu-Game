#ifndef BULLET_H
#define BULLET_H
#include "foreground.h"
#include <time.h>

class Bullet: public Foreground {
 public:
 /** Default constructor for bullet */
 Bullet (QPixmap *pm, int nx, int ny);
 /** Animates bullet */
 void move(int count); 
 /** Makes bullet disappear when it hits other objects */
 void collideUp(int num);
 /** Triggers bullet to sink when jumped on */
 void collideDown(int num);
 /** Returns if bullet is sinking or not */
 bool sinking;
};

/** Default constructor- bullet's y pos is randomly generated and set.
 *  It's z value is set to 2 and sinking is set to false.
 *
 *  @param pointer to QPixmap
 *  @param x position
 *  @param y position 
 *  @return nothing
 */
Bullet::Bullet( QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 srand(time(NULL));
 int py = rand()%9;
 if(py<=2){
 py = -100;
 }
 else if(py<=5){
 py = -70;
 }
 else{
 py = -200;
 }
 state = 2;
 setPos(768, py);
 setZValue(2);
 sinking = false;
}

/** Moves bullet back 2 pixels forward when a duration has elapsed and
 *  it isn't sinking. If it is sinking it moves down 2 pixels.
 *
 * @param count of how much time has elapsed since start of game
 * @return nothing
 */
void Bullet::move(int count) {
if(count%2 == 0){
 if(sinking == false){
  moveBy(-2, 0);
 }
 else{
  moveBy(0, 2);
 }
}
}

/** If object collides with bullet and bullet is above object this function is called
 *  If the case isn't special the bullet will disappear.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void Bullet::collideUp(int num){
 if(num == 0){
  setVisible(false);
 }
}

/** If object collides with bullet and bullet is above object this function is called
 *  If the case isn't special the sinking will be set to true.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void Bullet::collideDown(int num){
 if(num == 0){
   sinking = true;
 }
}

#endif // BULLET_H
