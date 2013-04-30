#ifndef SPIKE_H
#define SPIKE_H
#include "foreground.h"

class Spike: public Foreground {
 public:
 /** Default constructor for spike */
 Spike(QPixmap *pm, int nx, int ny);
 /** Animates spike */
 void move(int count); 
 /** Makes spike fall or bounce back up */
 void fall(int vy);
 /** Makes spike disappear when it hits other objects */
 void collideUp(int num);
 /** Makes spike disappear when it hits other objects */
 void collideDown(int num);
 /** Net y distance spike has traveled */
 int ty;
 /** Duration of fall/bounce back */
 double time;
 /** If spike should bounce or not */
 bool bounce;
};


/** Default constructor- spike's state is set to -1 because of it's bounce
 *  feature and it's zValue is set to 4 above the ground and most other things.
 *  Bounce is set to false.
 *
 *  @param pointer to QPixmap
 *  @param x position
 *  @param y position 
 *  @return nothing
 */
Spike::Spike( QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 state = -1;
 bounce = false;
 ty = 0;
 time = 0;
 setZValue(4);
}

/** Calls fall function when a duration has elapsed. If bounce is false
 *  the initial velocity is set to zero. If bounce is true it is set to 65.
 *
 * @param count of how much time has elapsed since start of game
 * @return nothing
 */
void Spike::move(int count) {
if(count%2 == 0){
 if(bounce == false){
   fall(0);
  }
  else{
   fall(65);
  }
}
}

/** Sets spike's initial y velocity to passed in parameter. Finds two y
 *  values based on the time (increases by 0.1 in between them). 
 *  The spike then moves the difference of the y values.
 *
 */
void Spike::fall(int vy){
int vi = vy;
  float yi = vi*time + -5*time*time;
  time += .1;
  float yf = vi*time + -5*time*time;
  if((yi-yf) < 0){
    vY = -1;
  }
  else if((yi-yf) > 0){
    vY = 1;
  }
  ty += (yi-yf);
  moveBy(0, yi-yf); 
}

/** If object collides with spike and spike is above object this function is called
 *  If the case isn't special the spike will disappear.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void Spike::collideUp(int num){
 if(num == 0){
  setVisible(false);
 }
}

/** If object collides with spike and spike is above the object this function is called
 *  If the case is 1, bounce is true and time is set to zero for a new jump.
 *  If the case isn't special the spike will disappear.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void Spike::collideDown(int num){
 if(num == 1){
  time = 0;
  bounce = true;
 }
 else if(num == 0){
  setVisible(false);
 }
}

#endif // SPIKE_H
