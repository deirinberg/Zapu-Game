#ifndef FOREGROUND_H
#define FOREGROUND_H
#include "object.h"

class Foreground: public Object {
public:
Foreground(QPixmap *pm, int nx, int ny);
virtual void move(int count) = 0; 
virtual void keySignal(QKeyEvent *e) = 0;
virtual void keyRelease(QKeyEvent *r) = 0;
virtual void setGround(int y) = 0;
virtual void collideUp(int num) = 0;
virtual void collideDown(int num) = 0;
};

#endif // FOREGROUND_H
