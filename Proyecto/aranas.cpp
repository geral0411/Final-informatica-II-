/*


 Clase Arañas: enemigo del mundo2

 */

#include "aranas.h"
#include "Personaje.h"

// se carga la imagen y se inicia el timer asociado
Aranas::Aranas(int inicio,int fin,QGraphicsItem *parent) : QGraphicsItem(parent)
{
    inicioPos=inicio;
    finPos=fin;
    direccion = 1;
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/imagenes/sprites_araña.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextSprite()));
    timer->start(100);
}

//Variación del sprite que esta asociada al timer(SLOT) y verifica la colisión
void Aranas::nextSprite()
{
    posSprite += 200;
    if(posSprite >= 798)posSprite = 0;

    if(this->pos().y() < inicioPos|| this->pos().y() > finPos) {//movimiento
        direccion = -direccion;
        setTransform(QTransform(-direccion, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(this->pos().x(),this->pos().y()+(direccion*7));

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Personaje)){

            emit estadoJuego(2);
            return;
        }
    }
}

//Margen de la imagen
QRectF Aranas::boundingRect() const {

    return QRectF(0,0,200,205);
}

//Se dibuja el objeto en la escena a partir del sprite
void Aranas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,200, 205);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Aranas::type() const
{
    return Type;

}
