#include "background.h"

/** Default constructor for background, inherited by background objects
 *  which include Ground items.
 *
 *  @param pointer to QPixmap
 *  @param x position
 *  @param y position 
 *  @return nothing
 */
Background::Background(QPixmap *pm, int nx, int ny) : Object( pm, nx, ny ) {

}
