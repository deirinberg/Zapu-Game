#ifndef FOREGROUND_H
#define FOREGROUND_H
#include "object.h"

class Foreground: public Object {
public:
/** Default constructor for foreground object */
Foreground(QPixmap *pm, int nx, int ny);
/** Default destructor for foreground object */
~Foreground();
/** Returns point to object's pixmap */
QPixmap* getPixmap();
/** Returns x velocity */
int getVX();
/** Returns y velocity */
int getVY();
/** Returns state of object */
int getState();
/** Sets x velocity to passed in parameter */
void setVX(int vx);
/** Sets state to passed in parameter */
void setState(int st);
/** Virtual function for moving, animating objects */
virtual void move(int count) = 0; 
/** Virtual function for handling a type of collision */
virtual void collideUp(int num) = 0;
/** Virtual function for handling a type of collision */
virtual void collideDown(int num) = 0;
};

#endif // FOREGROUND_H
