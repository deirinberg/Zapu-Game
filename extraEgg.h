#ifndef EXTRAEGG_H
#define EXTRAEGG_H
#include "foreground.h"

class ExtraEgg: public Foreground {
 public:
 ExtraEgg(QPixmap *pm, int nx, int ny);
 void move(int count); // Implement the move method
 void collideUp(int num);
 void collideDown(int num);
};

ExtraEgg::ExtraEgg( QPixmap *pm, int nx, int ny ) : Foreground( pm, nx, ny ) {
 state = 7;
 setZValue(1);
}
void ExtraEgg::move(int count) {
if(count%3 == 0){
 moveBy(-2, 0);
}
}

void ExtraEgg::collideUp(int num){
 if(num!=-1){
  setVisible(false);
 }
}

void ExtraEgg::collideDown(int num){
 if(num!=-1){
  setVisible(false);
 }
}


#endif // EXTRAEGG_H
