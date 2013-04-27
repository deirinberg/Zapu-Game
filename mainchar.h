#ifndef MAINCHAR_H
#define MAINCHAR_H
#include "foreground.h"
#include <cmath>

class MainChar: public Foreground {
 public:
 MainChar (QPixmap *pm, int nx, int ny);
 void move(int count); 
 void keySignal(QKeyEvent *e);
 void keyRelease(QKeyEvent *r);
 void setGround(int y);
 void collideUp(int num);
 void collideDown(int num);
 void walk();
 void crouch();
 void hurting();
 void jump(int num);
 int num;
 int vY;
 int floor;
 double time;
 double ty;
 bool fall;
 bool stopWalking;
 bool walking;
 bool pause;
 bool lost;
 bool jumping;
 bool dj;
 bool doubleJump;
 bool egg;
 private:
 QPixmap *yw1;
 QPixmap *yw2;
 QPixmap *yw3;
 QPixmap *yw4;
 QPixmap *yw5;
 QPixmap *yw6;
 QPixmap *yw7;
 QPixmap *yw8;
 QPixmap *jump1;
 QPixmap *jump2;
 QPixmap *jump3;
 QPixmap *jump4;
 QPixmap *jump5;
 QPixmap *jump6;
 QPixmap *jump7;
 QPixmap *jump8;
 QPixmap *jump9;
 QPixmap *jump10;
 QPixmap *jump11;
 QPixmap *egg2;
 QPixmap *hurt;
};

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
void MainChar::move(int count) {
if(lost == false){
 if(count%60 == 0){
  if(walking == true){
   egg = false;
   jumping = false;
   dj = false;
   doubleJump = false;
   walk();
  }
  else if(egg == true && num <=2){
   crouch();
  }
 }
}
 if(count%4 == 0){
  if(jumping == true){
   jump(50);
  }
 }
}

void MainChar::collideUp(int num){
 //bullet case
 if(lost == false && num == 0){
  jumping = true;
  time = 0;
  cout<<"YOSHI SHOULD JUMP\n";
  jump(30);
 }
}

void MainChar::collideDown(int num){
//bullet case
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

void MainChar::keySignal(QKeyEvent *e){
 switch(e->key()){
   case Qt::Key_Up:
      cout<<"UP KEY\n";
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
         cout<<"DOUBLE JUMP\n";
         doubleJump = true;
       }
       break;
   case Qt::Key_Right:
     if(jumping == false && egg == false && stopWalking == false){
      walking = true;
      vX = 1;
     }
     else if(jumping == false && egg == false){
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
      cout<<"LEFT KEY\n"; 
      break;
   case Qt::Key_Space:
     cout<<"SPACE KEY\n";
     break;
  }
}

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
      cout<<"RELEASE DOWN KEY\n";
      if(egg == true){
        egg = false;
        walk();
        num = 0;
       }
       break;
   case Qt::Key_Left:
      stopWalking = true;
      break;
   case Qt::Key_Space:
     cout<<"SPACE KEY\n";
     break;
  }
}

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
void MainChar::crouch(){
 setPixmap(*egg2);
}

void MainChar::hurting(){
 setPixmap(*hurt);
 walking = false;
 vX = 0;
 egg = false;
}

void MainChar::jump(int num){
  QPixmap *pm = jump1;
  int vi = num;
  if(fall == true){
    walking = false;
    vi = 0;
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
  if((yi-yf) < 0){
    vY = -1;
  }
  else if((yi-yf) > 0){
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
  //cout<<"TY: "<<ty<<endl;
  if(ty > 10){
   floor = 10000;
  }
  if(ty > 110){
   lost = true;
   vX = 0;
   cout<<"LOST IS TRUE\n";
  }
  if((yf-yi)>0 || ty < floor){
    moveBy(0, yi-yf); 
   if(pos().y() < -326){
    moveBy(0, -pos().y()-326);
   }
   if(ty > 100){
    walking = false;
   }
  }
  else{
   if(lost == false){
   setPos(pos().x(), floor-55);
   }
   else{
   cout<<"GOOD VUN\n";
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
