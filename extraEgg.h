#ifndef EXTRAEGG_H
#define EXTRAEGG_H
#include "foreground.h"

class ExtraEgg: public Foreground {
 public:
 /** Default constructor */
 ExtraEgg(QPixmap *pm, int nx, int ny);
 /** Animates egg */
 void move(int count); 
 /** Makes egg disappear when main character hits it */
 void collideUp(int num);
 /** Makes egg disappear when main character hits it */
 void collideDown(int num);
};

/** Default constructor- sets state to 7 and zValue to 1 above ground objects
 *
 *  @param pointer to QPixmap
 *  @param x position
 *  @param y position 
 *  @return nothing
 */
ExtraEgg::ExtraEgg( QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 state = 7;
 setZValue(1);
}
/** Moves egg back 2 pixels back when a duration has elapsed
 *
 * @param count of how much time has elapsed since start of game
 * @return nothing
 */
void ExtraEgg::move(int count) {
if(count%3 == 0){
 moveBy(-2, 0);
}
}

/** If object collides with egg and egg is above object this function is called
 *  If the case isn't special the egg will disappear.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void ExtraEgg::collideUp(int num){
 if(num!=-1){
  setVisible(false);
 }
}

/** If object collides with egg and egg is below object this function is called
 *  If the case isn't special the egg will disappear.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void ExtraEgg::collideDown(int num){
 if(num!=-1){
  setVisible(false);
 }
}


#endif // EXTRAEGG_H
