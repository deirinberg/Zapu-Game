#ifndef UI_H
#define UI_H
#include <QGraphicsPixmapItem>

class UI: public QGraphicsPixmapItem {
public:
/** default constructor */
UI(QPixmap *pm, int nx, int ny, bool visible);
};

/** Default constructor- sets pixmap to QPixmap pointer dereferenced
 *  and the position to the passed in location. It sets the visibility
 *  based on that parameter and the zValue to be 5 to be ahead of all
 *  other objects.
 *
 *  @param pointer to QPixmap
 *  @param x position
 *  @param y position 
 *  @param if object should be visible or not
 *  @return nothing
 */
UI::UI( QPixmap* p, int nx, int ny, bool visible ) {
 setPixmap( *p ); 
 QGraphicsPixmapItem::setPos(nx, ny); 
 setVisible(visible);
 setZValue(5);
}


#endif // UI_H
