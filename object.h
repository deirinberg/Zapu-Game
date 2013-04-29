#ifndef OBJECT_H
#define OBJECT_H
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Object: public QGraphicsPixmapItem {
public:
Object (QPixmap *pm, int nx, int ny);
virtual void move(int count) = 0; //virtual function.
protected: 
int state;
int x;
int y;
int vX;
int vY; //Every thing has a origin and a velocity – maybe 0
QPixmap *pixMap; //Good idea. Explain later.
};

#endif // OBJECT_H
