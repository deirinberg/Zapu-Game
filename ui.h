#ifndef UI_H
#define UI_H
#include <QGraphicsPixmapItem>

class UI: public QGraphicsPixmapItem {
public:
UI(QPixmap *pm, int nx, int ny, bool visible);
};

UI::UI( QPixmap* p, int nx, int ny, bool visible ) {
setPixmap( *p ); //First Qt method that doesn’t take a pointer :->
QGraphicsPixmapItem::setPos(nx, ny); //how you set the position
setVisible(visible);
setZValue(3);
}


#endif // OBJECT_H
