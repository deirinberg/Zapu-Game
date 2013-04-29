#include "foreground.h"

Foreground::Foreground( QPixmap *pm, int nx, int ny ) : Object( pm, nx, ny ) {

}

void Foreground::setVX(int vx){
  vX = vx;
}

void Foreground::setState(int st){
  state = st;
}

int Foreground::getVX(){
 return vX;
}

int Foreground::getVY(){
 return vY;
}

int Foreground::getState(){
 return state;
}

Foreground::~Foreground(){
 delete pixMap;
}

QPixmap* Foreground::getPixmap(){
 return pixMap;
}
