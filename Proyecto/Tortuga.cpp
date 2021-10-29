/*

 Clase Tortuga : enemigo de primer mundo, que al colicionar reinicia el nivel
 */

#include "Tortuga.h"
#include "Personaje.h"

// se carga la imagen y se inicia el timer asociado
Tortuga::Tortuga(int inicio,int fin,QGraphicsItem *parent) : QGraphicsItem(parent)
{
    inicioPos=inicio;
    finPos=fin;
    direccion = 1;
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/imagenes/Tortuga.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextSprite()));
    timer->start(100);
}

//Variación del sprite que esta asociada al timer(SLOT) y verifica la colisión
void Tortuga::nextSprite()
{
    //Manejo de Sprites
    //Distancia en caada sprite
    posSprite += 108;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 759)
    {
        posSprite = 0;
    }
    if(this->pos().x() < inicioPos|| this->pos().x() > finPos) {//movimiento
        direccion = -direccion;
        setTransform(QTransform(-direccion, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(this->pos().x() + (direccion*7), this->pos().y());

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Personaje)){

            emit estadoJuego(1);
            return;
        }
    }
}

//Margen de la imagen
QRectF Tortuga::boundingRect() const {

    return QRectF(0,0,108,102);
}

//Se dibuja el objeto en la escena a partir del sprite
void Tortuga::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,108, 102);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Tortuga::type() const
{
    return Type;

}
