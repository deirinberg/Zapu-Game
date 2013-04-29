#ifndef FOREGROUND_H
#define FOREGROUND_H
#include "object.h"

class Foreground: public Object {
public:
Foreground(QPixmap *pm, int nx, int ny);
~Foreground();
QPixmap* getPixmap();
int getVX();
int getVY();
int getState();
void setVX(int vx);
void setState(int st);
virtual void move(int count) = 0; 
virtual void collideUp(int num) = 0;
virtual void collideDown(int num) = 0;
};

#endif // FOREGROUND_H
