#ifndef OBJECT_H
#define OBJECT_H
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Object: public QGraphicsPixmapItem {
public:
Object (QPixmap *pm, int nx, int ny);
virtual void move(int count) = 0; //virtual function. Class Thing is abstract. For a reason.
virtual void keySignal(QKeyEvent *e) = 0;
virtual void keyRelease(QKeyEvent *r) = 0;
private: //Every thing has a origin and a velocity – maybe 0
int x;
int y;
int vX;
int vY;
QPixmap *pixMap; //Good idea. Explain later.
};

#endif // OBJECT_H
