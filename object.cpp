#include "object.h"
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QLabel>
using namespace std;
Object::Object( QPixmap* p, int nx, int ny ) {
pixMap = p; //Handy to store separate to get image width/height, etc.
setPixmap( *p ); //First Qt method that doesn’t take a pointer :->
x = nx;
y = ny;
setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
QGraphicsPixmapItem::setPos(x+500, y+500); //how you set the position
}

