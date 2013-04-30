#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "object.h"

class Background: public Object {
 public:
 /** Default Background constructor */
 Background (QPixmap *pm, int nx, int ny);
 /** sets how many ground piece options there are */ 
 virtual void setLimit(int num) = 0;
 /** virtual function for moving the background */
 virtual void move(int count) = 0; // Implement the move method
};


#endif // BACKGROUND_H
