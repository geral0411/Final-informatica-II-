/*

 Clase Next2: objeto del segundo mundo, que al colisionar con el conejo le da la victoria defintiva

 */

#include "next2.h"
#include "Personaje.h"

//Costructor donde se carga la imagen y se inicia el timer asociado
Next2::Next2(QGraphicsItem *parent) : QGraphicsItem(parent)
{

    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/imagenes/next.png");
    QTimer *timer3 = new QTimer(this);
    connect(timer3,SIGNAL(timeout()),this,SLOT(colision()));
    timer3->start(100);
    posSprite=0;
}

//Se verifica la colisión asociada al timer(SLOT)
void Next2::colision()
{

      QList<QGraphicsItem *> colliding_items = collidingItems();
     //If one of the colliding items is an Enemy, destroy both the bullet and the enemy
     for (int i = 0, n = colliding_items.size(); i < n; ++i){
         if (typeid(*(colliding_items[i])) == typeid(Personaje)){

             emit estadoJuego(4);
             return;
         }
     }
}

//Se define la margen del objeto
QRectF Next2::boundingRect() const {

    return QRectF(0,0,116,126);
}

//Se dibuja el objeto en la escena a partir del sprite
void Next2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,116, 126);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Next2::type() const
{
    return Type;
}
