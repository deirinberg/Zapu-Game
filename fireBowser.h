#ifndef FIREBOWSER_H
#define FIREBOWSER_H
#include "foreground.h"

class FireBowser: public Foreground {
 public:
 /** Default constructor for fire bowser */
 FireBowser(QPixmap *pm, int nx, int ny);
 /** Animates Fire Bowser */
 void move(int count); 
 /** Makes fire bowser disappear when it hits other objects */
 void collideUp(int num);
 /** Makes fire bowser change images when hit with bolts */
 void collideDown(int num);
 /** Makes fire bowser appear to walk */
 void walk(int count);
 /** Returns if fire bowser should appear shocked or not */
 bool shocked;
 /** Measure of how much health bowser has left. */
 int health;
};

/** Default constructor- sets pos to parameters (ny-75 = ground),
 *  zValue to 2 so above ground and state to 3 because it reacts
 *  to bolts. Health is initially set to 5.
 *
 *  @param pointer to QPixmap
 *  @param x position
 *  @param y position 
 *  @return nothing
 */
FireBowser::FireBowser(QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 setPos(768, ny-75);
 setZValue(2);
 state = 5;
 health = 3;
}

/** Moves bowser forward 2 pixels forward when a duration has elapsed and
 *  it isn't shocked. If it is shocked it sets it to false so it can move
 *  next time. If a longer time has elapsed and bowser is still alive walk()
 *  will be called.
 *
 * @param count of how much time has elapsed since start of game
 * @return nothing
 */
void FireBowser::move(int count) {
if(count%4 == 0){
 if(shocked == false){
  moveBy(-2, 0);
 }
 else if(shocked == true){
  shocked = false;
 }
}
if(count%50 == 0 && health != 0){
 walk(count);
}
}

/** Alternates images to make bowser appear like he's walking
 *
 *  @param count of how much time has elapsed since start of game
 *  @return nothing
 */
void FireBowser::walk(int count){
 if(pos().y()>-100){
  if(count%100 == 0){
   setPixmap(qApp->applicationDirPath()+"/Pictures/FBWalk1.png");
  }
  else{
   setPixmap(qApp->applicationDirPath()+"/Pictures/FBStand.png");
  }
 }
 else if(pos().y()>-125){
  setPixmap(qApp->applicationDirPath()+"/Pictures/FBJump1.png");
 }
 else{
  setPixmap(qApp->applicationDirPath()+"/Pictures/FBJump2.png");
 }
 if(count%800 == 0){
  setPixmap(qApp->applicationDirPath()+"/Pictures/FBFire.png");
 }
}

/** If object collides with bowser and bowser is above object this function is called
 *  If the case isn't special the bowser will disappear.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void FireBowser::collideUp(int num){
 if(num == 0){
  setVisible(false);
 }
}

/** If object collides with bowser and bowser is below object this function is called
 *  If the case is 3 (bolts) bowser's image will be set to look shocked and shocked
 *  will be set to true, health will also decrease by one. If bowser doesn't have
 *  any health, it's image will change to hurt and it's state will be set to 4
 *  since it isn't harmful anymore.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void FireBowser::collideDown(int num){
 if(num == 3){
  if(health>0){
   setPixmap(qApp->applicationDirPath()+"/Pictures/FBShock.png");
   shocked = true;
   health--;
   }
   else{
   setPixmap(qApp->applicationDirPath()+"/Pictures/FBHurt.png");
   shocked = false;
   state = 4;
   }
 }
}

#endif // FIREBOWSER_H
