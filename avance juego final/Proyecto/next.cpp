/*


 Clase Next: objeto del primer mundo, que al colisionar con el conejo le da al paso al mundo 2

 */
#include "next.h"
#include "Personaje.h"

//Costructor donde se carga la imagen y se inicia el timer asociado
Next::Next(QGraphicsItem *parent) : QGraphicsItem(parent)
{

    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/imagenes/next.png");
    QTimer *timer3 = new QTimer(this);
    connect(timer3,SIGNAL(timeout()),this,SLOT(nextSprite()));
    timer3->start(100);
}

//Variación del sprite que esta asociada al timer(SLOT) y verifica la colisión
void Next::nextSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 116;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 350)
    {
        posSprite = 0;
    }
    //setTransform(QTransform(-direccion, 0, 0, 1, boundingRect().width(), 0));
     setPos(this->pos().x(), this->pos().y());

      QList<QGraphicsItem *> colliding_items = collidingItems();
     //If one of the colliding items is an Enemy, destroy both the bullet and the enemy
     for (int i = 0, n = colliding_items.size(); i < n; ++i){
         if (typeid(*(colliding_items[i])) == typeid(Personaje)){

             emit estadoJuego(0);
             return;
         }
     }
}

//Margen de la imagen
QRectF Next::boundingRect() const {

    return QRectF(0,0,116,126);
}

//Se dibuja el objeto en la escena a partir del sprite
void Next::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,116, 126);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Next::type() const
{
    return Type;
}
