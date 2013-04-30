#ifndef SPIKE_H
#define SPIKE_H
#include "foreground.h"

class Spike: public Foreground {
 public:
 Spike(QPixmap *pm, int nx, int ny);
 void move(int count); // Implement the move method
 void fall(int vy);
 void collideUp(int num);
 void collideDown(int num);
 int ty;
 double time;
 bool bounce;
};

Spike::Spike( QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 state = -1;
 bounce = false;
 ty = 0;
 time = 0;
 setZValue(4);
}
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
  cout<<"SPIKE: "<<ty<<endl;
  moveBy(0, yi-yf); 
}

void Spike::collideUp(int num){
 if(num == 0){
  setVisible(false);
 }
}

void Spike::collideDown(int num){
//yoshi case
 if(num == 1){
  time = 0;
  bounce = true;
 }
 else if(num == 0){
  setVisible(false);
 }
}

#endif // BULLET_H
