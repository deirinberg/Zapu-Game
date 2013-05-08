#ifndef HEATBULLET_H
#define HEATBULLET_H
#include "foreground.h"

class HeatBullet: public Foreground {
 public:
 /** Default constructor for bullet */
 HeatBullet (QPixmap *pm, int nx, int ny);
 /** Animates heat bullet */
 void move(int count); 
 /** Makes heat bullet disappear when it hits other objects */
 void collideUp(int num);
 /** Triggers heat bullet to sink when jumped on */
 void collideDown(int num);
 /** Returns if heat bullet is sinking or not */
 bool sinking;
};

/** Default constructor- heat bullet's y pos is set to Zapu's y value and it's state is set to -2 so it's y position can change to Zapu's y direction. 
 *  It's z value is set to 2 and sinking is set to false.
 *
 *  @param pointer to QPixmap
 *  @param x position
 *  @param y position 
 *  @return nothing
 */
HeatBullet::HeatBullet( QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 srand(time(NULL));
 int py = ny;
 state = -2;
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
void HeatBullet::move(int count) {
if(count%3 == 0){
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
void HeatBullet::collideUp(int num){
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
void HeatBullet::collideDown(int num){
 if(num == 0){
   sinking = true;
 }
}

#endif // BULLET_H
