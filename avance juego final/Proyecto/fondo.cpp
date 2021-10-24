/*


 Clase fondo: se hace uso de la herencia, para generar un shape(),
 que permitiran agregar y ubicar en la escena objetos que no tiene funcionalidad
 alguna tales como: fondos, nivel del suelo e imagen del cazad

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
