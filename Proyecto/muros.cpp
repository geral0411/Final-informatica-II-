/*

Clase muros: objeto del mapa sobre el cual camina el personaje

*/
#include "muros.h"
#include <QPainter>

//Se carga la imagen y la cantidad de muros que se deseen poner en fila
Muros::Muros(int longitud,QGraphicsItem *parent): QGraphicsItem(parent)

{
    tamano=longitud;
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/imagenes/plataforma.png");
    posSprite = 0;

}

//Se define la margen del objeto a partir del tamaño
QRectF Muros::boundingRect() const {
    return QRectF(0,0,125*tamano,56);

}

//Se dibuja el objeto en la escena a partir del sprite y de su tamaño
void Muros::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    for(int i = 0; i < 125*tamano; i++)
    {
        painter->drawPixmap(i*125,0, sprite, posSprite, 0,125, 56);
    }
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int Muros::type() const
{
    return Type;
}
