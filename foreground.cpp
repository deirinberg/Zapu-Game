#include "foreground.h"

/** Default constructor for foreground, inherited by foreground objects
 *  which include main character and things. Separate from ground items.
 *
 *  @param pointer to QPixmap
 *  @param x position
 *  @param y position 
 *  @return nothing
 */
Foreground::Foreground( QPixmap *pm, int nx, int ny ) : Object( pm, nx, ny ) {

}

/** Sets the x velocity
 *
 *  @param x speed with direction
 *  @return nothing
 */
void Foreground::setVX(int vx){
  vX = vx;
}

/** Sets the state
 *
 *  @param integer representing state of object
 *  @return nothing
 */
void Foreground::setState(int st){
  state = st;
}

/** 
 *  @return x velocity
 */
int Foreground::getVX(){
 return vX;
}

/** 
 *  @return y velocity
 */
int Foreground::getVY(){
 return vY;
}

/** 
 *  @return current state
 */
int Foreground::getState(){
 return state;
}

/** Deletes pixmap pointer passed in
 *
 *  @return nothing
 */
Foreground::~Foreground(){
 delete pixMap;
}

/** 
 *  @return pixmap pointer of object
 */
QPixmap* Foreground::getPixmap(){
 return pixMap;
}
