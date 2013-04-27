#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "object.h"

class Background: public Object {
 public:
 Background (QPixmap *pm, int nx, int ny);
 virtual void setLimit(int num) = 0;
 virtual void move(int count) = 0; // Implement the move method
};


#endif // BACKGROUND_H
