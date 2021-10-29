/*


 Clase casa: objeto para que permite finalizar el juego

 */

#include "casa.h"
#include "Personaje.h"

//Costructor donde se carga la imagen y se inicia el timer asociado
casa::casa(QGraphicsItem *parent) : QGraphicsItem(parent)
{

    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/imagenes/Casa_ardilla.png");
    posSprite = 0;
    QTimer *timer3 = new QTimer(this);
    connect(timer3,SIGNAL(timeout()),this,SLOT(nextSprite()));
    timer3->start(100);
}

//Variación del sprite que esta asociada al timer(SLOT) y verifica la colisión
void casa::nextSprite()
{
     QList<QGraphicsItem *> colliding_items = collidingItems();
     for (int i = 0, n = colliding_items.size(); i < n; ++i){
         if (typeid(*(colliding_items[i])) == typeid(Personaje)){

             emit estadoJuego(4);
             return;
         }
     }
}

//Margen de la imagen
QRectF casa::boundingRect() const {

    return QRectF(0,0,220,175);
}

//Se dibuja el objeto en la escena a partir del sprite
void casa::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,220,175);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)

}

int casa::type() const
{
    return Type;
}

int casa::heigth()
{
    return sprite.height();
}

