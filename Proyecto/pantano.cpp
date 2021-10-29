/*

 Clase pantano: objeto del primer mundo, que cambia el mov del personaje

 */
#include "pantano.h"
#include "Personaje.h"

//en el constructor se carga la imagen
pantano::pantano(QGraphicsItem *parent): QGraphicsItem(parent)

{
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/imagenes/pantano.png");
    QTimer *timer3 = new QTimer(this);
    connect(timer3,SIGNAL(timeout()),this,SLOT(colision()));
    timer3->start(100);
    posSprite=0;
}

//Se verifica colicion con personaje
bool pantano::colision()
{

     QList<QGraphicsItem *> colliding_items = collidingItems();
     for (int i = 0, n = colliding_items.size(); i < n; ++i){
         if (typeid(*(colliding_items[i])) == typeid(Personaje))
             return true;
     }
     return false;
}
// se define la margen del objeto
QRectF pantano::boundingRect() const
{
    return QRectF(0,0,190,21);
}

//Se dibuja el objeto en la escena a partir del sprite
void pantano::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,190,21);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int pantano::type() const
{
    return Type;
}
