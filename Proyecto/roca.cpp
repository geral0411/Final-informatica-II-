/*


 Clase roca: enemigo del tercer mundo, que al colicionar reinicia el nivel

  ECUACIONES:caída libre

    Y(t)=y(t-1)+v(t-1)*T-g/2*T*T
    V(t)=V(t-1)-g*T
    posy=H-(0.5*g*T*T);

 */


#include "roca.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include "halcon.h"
#include "mundos.h"
#include "Personaje.h"

//Se carga la imagen y se inicia el timer asociado
Roca::Roca(float x,QGraphicsItem *parent) : QGraphicsItem(parent)
{

    posx=x;
    sprite=QPixmap(":/imagenes/Roca.png");
    timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(move()));
    timer2->start(int(1000*T));
    //timer2->start(50);

}

QRectF Roca::boundingRect() const
{
    return QRectF(0,0,200,200);
}

//Se dibuja el objeto en la escena a partir del sprite
void Roca::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,200, 200);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Roca::type() const
{
    return Type;
}

// describe el movimiento parabólico de las rocas y verifica la colisión
void Roca::move()
{

    float t=5*T;

    posy=posy+v*t+(0.5*g*t*t);
    v=v+g*t;
    posx=posx+Vx*T*direccion;
    setPos(posx,posy);

    if(pos().y()>600){
        var=0;

    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0; i < colliding_items.size(); ++i){
        if(typeid (*(colliding_items[i]))== typeid (Personaje)){
            colis=true;

        }
    }

}
