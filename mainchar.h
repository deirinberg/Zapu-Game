#ifndef MAINCHAR_H
#define MAINCHAR_H
#include "foreground.h"
#include <cmath>
#include <QApplication>
#include <iostream>
using namespace std;

class MainChar: public Foreground {
 public:
 /** Default Constructor */
 MainChar (QPixmap *pm, int nx, int ny);
 /** Animates Main Character */
 void move(int count); 
 /** Called when key is pressed */
 void keySignal(QKeyEvent *e);
 /** Called when key is released */
 void keyRelease(QKeyEvent *r);
 /** Sets x velocity */
 void setVX(int vx);
 /** Returns y velocity */
 int getVY();
 /** Sets ground level */
 void setGround(int y);
 /** Returns ground level */
 int getGround();
 /** Sets state */
 void setState(int s);
 /** Called when main character collides with and is above thing */
 void collideUp(int num);
 /** Called when main character collides with and is below thing */
 void collideDown(int num);
 /** Makes character appear walking */
 void walk();
 /** Stops character and puts it in an egg  */
 void crouch();
 /** Makes character appear to be hurt (lose life) */
 void hurting();
 /** Makes character jump */
 void jump(int num);
 /** Keeps track of image on walking gif */
 int num;
 /** Y velocity */
 int vY;
 /** Ground level */
 int floor;
 /** How much time has elapsed since start of jump */
 double time;
 /** Total net y distance of jump */
 double ty;
 /** If character should fall */
 bool fall;
 /** Says if character should stop walking or not when right key is pressed */
 bool stopWalking;
 /** Returns if character is currently walking or not */
 bool walking;
 /** Stores if character was walking before jump */ 
 bool pause;
 /** Returns if character has collided with bad thing and lost */
 bool lost;
 /** Returns if character is jumping or not */
 bool jumping;
 /** Returns if a double jump has been attempted */
 bool dj;
 /** Returns if a double jump has occurred */
 bool doubleJump;
 /** Returns if character is in an egg or not */
 bool egg;
 private:
 /** Zapu Walking Pixmap item */
 QPixmap *yw1;
 /** Zapu Walking Pixmap item */
 QPixmap *yw2;
 /** Zapu Walking Pixmap item */
 QPixmap *yw3;
 /** Zapu Walking Pixmap item */
 QPixmap *yw4;
 /** Zapu Walking Pixmap item */
 QPixmap *yw5;
 /** Zapu Walking Pixmap item */
 QPixmap *yw6;
 /** Zapu Walking Pixmap item */
 QPixmap *yw7;
 /** Zapu Walking Pixmap item */
 QPixmap *yw8;
 /** Zapu Jumping Pixmap item */
 QPixmap *jump1;
 /** Zapu Jumping Pixmap item */
 QPixmap *jump2;
 /** Zapu Falling Pixmap item */
 QPixmap *jump3;
 /** Zapu Double Jump Pixmap item */
 QPixmap *jump4;
 /** Zapu Double Jump Pixmap item */
 QPixmap *jump5;
 /** Zapu Double Jump Pixmap item */
 QPixmap *jump6;
 /** Zapu Double Jump Pixmap item */
 QPixmap *jump7;
 /** Zapu Double Jump Pixmap item */
 QPixmap *jump8;
 /** Zapu Double Jump Pixmap item */
 QPixmap *jump9;
 /** Zapu Double Jump Pixmap item */
 QPixmap *jump10;
 /** Zapu Double Jump Pixmap item */
 QPixmap *jump11;
 /** Zapu Egg Pixmap item */
 QPixmap *egg2;
 /** Zapu Hurt Pixmap item */
 QPixmap *hurt;
};

/** Default constructor- sets default values (all false/off) or 0.
 *  zValue is set to 2 which is in front of ground. Sets QPixmaps
 *  to appropriate images.
 *
 *  @param pointer to QPixmap
 *  @param x position
 *  @param y position 
 *  @return nothing
 */
MainChar::MainChar(QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 floor = 0;
 num = 0;
 vX = 0;
 vY = 0;
 setZValue(2);
 walking = false;
 egg = false;
 fall = false;
 jumping = false;
 doubleJump = false;
 stopWalking = false;
 lost = false;
 pause = false;
 state = 0;
 yw1 = new QPixmap(qApp->applicationDirPath()+"/Pictures/YW1.png");
 yw2 = new QPixmap(qApp->applicationDirPath()+"/Pictures/YW2.png");
 yw3 = new QPixmap(qApp->applicationDirPath()+"/Pictures/YW3.png");
 yw4 = new QPixmap(qApp->applicationDirPath()+"/Pictures/YW4.png");
 yw5 = new QPixmap(qApp->applicationDirPath()+"/Pictures/YW5.png");
 yw6 = new QPixmap(qApp->applicationDirPath()+"/Pictures/YW6.png");
 yw7 = new QPixmap(qApp->applicationDirPath()+"/Pictures/YW7.png");
 yw8 = new QPixmap(qApp->applicationDirPath()+"/Pictures/YW8.png");
 jump1 = new QPixmap(qApp->applicationDirPath()+"/Pictures/Jump1.png");
 jump2 = new QPixmap(qApp->applicationDirPath()+"/Pictures/Jump2.png");
 jump3 = new QPixmap(qApp->applicationDirPath()+"/Pictures/Jump3.png");
 jump4 = new QPixmap(qApp->applicationDirPath()+"/Pictures/Jump4.png");
 jump5 = new QPixmap(qApp->applicationDirPath()+"/Pictures/Jump5.png");
 jump6 = new QPixmap(qApp->applicationDirPath()+"/Pictures/Jump6.png");
 jump7 = new QPixmap(qApp->applicationDirPath()+"/Pictures/Jump7.png");
 jump8 = new QPixmap(qApp->applicationDirPath()+"/Pictures/Jump8.png");
 jump9 = new QPixmap(qApp->applicationDirPath()+"/Pictures/Jump9.png");
 jump10 = new QPixmap(qApp->applicationDirPath()+"/Pictures/Jump10.png");
 jump11 = new QPixmap(qApp->applicationDirPath()+"/Pictures/Jump11.png");
 egg2 = new QPixmap(qApp->applicationDirPath()+"/Pictures/Egg2.png");
 hurt = new QPixmap(qApp->applicationDirPath()+"/Pictures/Hurt.png");
}

/** If the game is still going and the appropriate time duration has
 *  elapsed walk() will be called if the character can walk. Crouch()
 *  will be called is the character can become an egg. The character
 *  will jump() at a higher frequency with an initial velocity of 50 if
 *  jumping is true.
 *
 *  @param count of how much time has elapsed since start of game
 *  @return nothing
 */
void MainChar::move(int count) {
if(lost == false){
 if(count%25 == 0){
  if(walking == true && vX > 0){
   state = 0;
   vY = 0;
   egg = false;
   jumping = false;
   dj = false;
   doubleJump = false;
   walk();
  }
  else if(egg == true && num <=2){
   crouch();
   vY = 0;
  }
 }
}
 if(count%2 == 0){
  if(jumping == true){
   jump(50);
  }
 }
}

/** If the character collides with a thing and the character is above 
 *  the object this function is called. If the player hasn't lost and
 *  and the case is 0 (bullet). The player will receive an extra 
 *  small bounce jump with initial velocity of 30. This doesn't
 *  affect double jumps.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void MainChar::collideUp(int num){
 if(lost == false && num == 0){
  jumping = true;
  time = 0;
  jump(30);
 }
}

/** If the character collides with a thing and the character is below 
 *  the object this function is called. If the case is 0 (default) 
 *  the character will stop moving and fall. If the character is below
 *  the floor it will be reset to the ground. hurting() will then be 
 *  called which will trigger a reset.
 *
 *  @param num that gives case of collision
 *  @return nothing
 */
void MainChar::collideDown(int num){
 if(num == 0){
  walking = false;
  lost = true;
 if(jumping == true){
  doubleJump = true;
  jump(0);
 }
 else if(pos().y() == (floor-55)){
  moveBy(0, -6);
 }
  hurting();
 }
}

/** Called when key is pressed from MainWindow class. If the up key
 *  is pressed jump() will be called if it hasn't already. The walk
 *  state will be held in the pause bool. Time will be reset. If a
 *  double jump is available double jump will be set to true. If
 *  the right key is pressed walking will be set to true if it is 
 *  false. If the character is already walking it will stop. If
 *  the down key is pressed egg will be set to true. If the left key
 *  is pressed the character will stop walking.
 *
 *  @param  QKeyEvent pointer that stores key pressed
 *  @return nothing
 */
void MainChar::keySignal(QKeyEvent *e){
 switch(e->key()){
   case Qt::Key_Up:
      if(jumping == false){
       if(walking == true){
         pause = true;
         walking = false;
        }
       jumping = true;
       ty = 0;
       time = 0;
       num = 0;
      }
      else if(dj == true){
         doubleJump = true;
       }
       break;
   case Qt::Key_Right:
     if(jumping == false && egg == false && stopWalking == false){
      walking = true;
      vX = 1;
      vY = 0;
     }
     else if(jumping == false && egg == false){
      vY = 0;
      vX = 0;
      num = 0;
      walk();
      num = 0;
      walking = false;
      stopWalking = false;
     }
      break;
   case Qt::Key_Down:
      if(egg == false && jumping == false){
        walking = false;
        egg = true;
        num = 0;
        vX = 0;
       }
       break;
   case Qt::Key_Left:
      walking = false;
      vX = 0;
      vY = 0;
      break;
  }
}

/** Called when key is released. If the up key is released and
 *  the character hasn't double jumped a double jump will be
 *  set to available. If the right or left key is release and 
 *  walking is stopWalking will be set to true. If the down key
 *  is pressed and the character is currently an egg it will return
 *  back to it's walking state. 
 *
 *  @param  QKeyEvent pointer that stores key released
 *  @return nothing
 */
void MainChar::keyRelease(QKeyEvent *e){
 switch(e->key()){
   case Qt::Key_Up:
       if(jumping == true && doubleJump == false){
         dj = true;
       }
       break;
   case Qt::Key_Right:
     if(walking == true){
      stopWalking = true;
      }
      break;
   case Qt::Key_Down:
      if(egg == true){
        state = 0;
        egg = false;
        walk();
        num = 0;
       }
       break;
   case Qt::Key_Left:
      stopWalking = true;
      break;
  }
}
/** Returns the y speed
 *
 *  @return positive or negative y velocity
 */
int MainChar::getVY(){
 return vY;
}

/** Sets the x velocity
 *
 *  @param x speed with direction
 *  @return nothing
 */
void MainChar::setVX(int vx){
 vX = vx;
 vY = 0;
 if(vX != -2){
  walking = false;
  egg = false;
  jumping = false;
  fall = false;
  doubleJump = false;
  stopWalking = false;
  lost = false;
  pause = false;
  state = 0;
 }
}

/** Sets the state of the character
 *
 *  @param state to change charater to
 *  @return nothing
 */
void MainChar::setState(int s){
 state = s;
}

/** Sets the floor based on what the current ground position is.
 *
 *  @param y position of current ground item
 *  @return nothing
 */
void MainChar::setGround(int num){
 if(pos().y() <= 20 && num == 20){
  floor = 0;
 }
 else if(pos().y() <= 3 && num == 3){
  floor = -17;
 }
 else if(pos().y() <= -14 && num == -14){
  floor = -34;
 }
 else if(num > 20){
  floor = 10000;
 }
}

/**
 *  @return y coordinate of floor level 
 */
int MainChar::getGround(){
 return floor;
}
/** Sets the state to 1 and changes the image to an egg
 *
 *  @return nothing
 */
void MainChar::crouch(){
 state = -1;
 setPixmap(*egg2);
}

/** Sets image to hurting and stops walking or egg from being called
 *  vX and state are set to -2.
 *
 *  @return nothing
 */
void MainChar::hurting(){
 setPixmap(*hurt);
 walking = false;
 vX = -2;
 state = -2;
 egg = false;
}

/** Sets image initially to start jump and initial velocity to passed in parameter.
 *  If fall is true the character will stop walking. If doubleJump is true the jump
 *  will reset and a new double jump will not be made available. Two positions will
 *  be calculated at 0.1 difference time intervals. vY (positive or negative) will
 *  be set based on the direction of the difference. If double jump is true the 
 *  image will be set based on the time elapsed. If the character is above the floor
 *  it's position will move by the difference of the two y values. If it goes through
 *  the ground when it's not supposed to it'll be reset. If there is a gap, however,
 *  the character will fall through it.
 *
 *  @param initial y velocity
 *  @return nothing
 */
void MainChar::jump(int num){
  QPixmap *pm = jump1;
  int vi = num;
  if(fall == true){
    walking = false;
   if(vX != -2){
    vi = 0;
   }
  }
  else if(doubleJump == true){
    vi = num;
   if(dj == true){
    time = 0;
    dj = false;
   }
  }
  float yi = vi*time + -5*time*time;
  time += .1;
  float yf = vi*time + -5*time*time;
  if(vX!=-2 && (yi-yf) < 0){
    vY = -1;
  }
  else if(vX != -2 && (yi-yf) > 0){
    vY = 1;
  }
  if(doubleJump == true && (yi - yf)<0){
   double t = time/0.4;
   int pic = (int)t;
    switch(pic){
     case 1: 
      pm = jump4; break;
     case 2: 
      pm = jump5; break;
     case 3: 
      pm = jump6; break;
     case 4: 
      pm = jump7; break;
     case 5: 
      pm = jump8; break;
     case 6: 
      pm = jump9; break;
     case 7: 
      pm = jump10; break;
     default:
      pm = jump11; break;
    }
  }
  else if(doubleJump == true){
    pm = jump3;
  }
  if(ty == 0 && doubleJump == false){
   pm = jump1;
  }
  else if((yi-yf)>0 && doubleJump == false){
   pm = jump3;
  }
  else if(doubleJump == false){
   pm = jump2;
  }
  ty += (yi-yf);
  if(ty > 10){
   floor = 10000;
  }
  if(ty > 110){
   lost = true;
   vX = 0;
  }
  if((yf-yi)>0 || ty < floor){
    moveBy(0, yi-yf); 
   if(pos().y() < -326){
    moveBy(0, -pos().y()-326);
    cout<<"HERE??? "<<pos().y()<<endl;
   }
   if(ty > 100){
    walking = false;
   }
  }
  else{
  if(vX!=-2){
    vY = 0;
   }
   if(lost == false){
   setPos(pos().x(), floor-55);
   }
   else{
   setPos(pos().x(), floor-72);
   }
   jumping = false;
   dj = false;
   doubleJump = false;
   if(pause == true){
    walking = true;
    pause = false;
   }
   pm = yw1;
  }
 if(lost == false){
  setPixmap(*pm);
  }
}

/** Doesn't allow walking if the character is below the floor. 
 *  If it is above it the image will be set based on the num
 *  which goes through walking animated images (to appear like
 *  a gif).
 *
 *  @return nothing
 */
void MainChar::walk(){
 if(floor > 0){
  fall = true;
  walking = false;
  jumping = true;
 }
 else{
  QPixmap *pm = yw1;
  switch(num){
   case 1: pm = yw2; break;
   case 2: pm = yw3; break;
   case 3: pm = yw4; break;
   case 4: pm = yw5; break;
   case 5: pm = yw6; break;
   case 6: pm = yw7; break;
   case 7: pm = yw8; break;
   }
   if(num <= 6){
    num++;
   }
   else{
    num = 0;
   }
  setPixmap(*pm);
  }
}

#endif // MAINCHAR_H
