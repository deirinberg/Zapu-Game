#ifndef OBJECT_H
#define OBJECT_H
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Object: public QGraphicsPixmapItem {
public:
/** Default Constructor */
Object (QPixmap *pm, int nx, int ny);
/** Virtual move function that animates stuff, used in child/grandchild classes */
virtual void move(int count) = 0; 
protected: 
/** Current state of item represented by integer */
int state;
/** X position of object */
int x;
/** Y position of object */
int y;
/** x velocity */
int vX;
/** y velocity */
int vY; 
/** Pointer to pixmap that is set */
QPixmap *pixMap; 
};

#endif // OBJECT_H
