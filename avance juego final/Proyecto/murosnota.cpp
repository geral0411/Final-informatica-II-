#include "murosnota.h"

//Se carga la imagen y la cantidad de muros que se deseen poner en fila
MurosNota::MurosNota(int _longitud, QGraphicsItem *parent) : QGraphicsItem(parent)

{
    longitud=_longitud;
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/imagenes/plataforma.png");
    posSprite = 0;
}

//Se define la margen del objeto a partir del tamaño
QRectF MurosNota::boundingRect() const
{
    return QRectF(0,0,63*longitud,63);
}

//Se dibuja el objeto en la escena a partir del sprite y de su tamaño
void MurosNota::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(int i = 0; i < 63*longitud; i++)
    {
        painter->drawPixmap(i*63,0, sprite, posSprite, 0,63, 63);
    }
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int MurosNota::type() const
{
    return Type;
}
