/*


 Clase fondo: shape(),permite agregar y ubicar en la escena objetos que no tiene funcionalidad


 */

#include "fondo.h"

Fondo::Fondo (const QPixmap &pixmap, QGraphicsItem * parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
}

QPainterPath Fondo::shape() const
{
    return QPainterPath();
}
