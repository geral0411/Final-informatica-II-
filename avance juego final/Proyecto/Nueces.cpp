#include "Nueces.h"


//en el constructor se carga la imagen
Nueces::Nueces(QGraphicsItem *parent): QGraphicsItem(parent)

{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/imagenes/nuez.png");
    posSprite=0;
}

Nueces::~Nueces()
{

}

// se define la margen del objeto
QRectF Nueces::boundingRect() const
{
    return QRectF(0,0,45,60);
}

//Se dibuja el objeto en la escena a partir del sprite
void Nueces::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,45,60);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Nueces::type() const
{
    return Type;
}
