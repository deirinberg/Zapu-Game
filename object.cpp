#include "object.h"
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QLabel>
using namespace std;
/** Default constructor sets pixMap to passed in pixMap
 *  and sets the pixmap to the dereferenced pointer. X
 *  and y are set to the passed in coordinates and 
 *  the positiion is set to this location.
 *
 *  @param pointer to QPixmap
 *  @param x position
 *  @param y position 
 *  @return nothing
 */
Object::Object( QPixmap* p, int nx, int ny ) {
pixMap = p; 
setPixmap( *p ); 
x = nx;
y = ny;
setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
QGraphicsPixmapItem::setPos(x, y); 
}

