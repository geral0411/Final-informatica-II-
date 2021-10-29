/*


 Clase fisica3: enemigo del mundo2, que presenta el mov circular en la escena.

   ECUACIONES DE MOV CIRCULAR UNIFORME:
    X(n)=(X(n-1)-Cx)*cos(wT)-(Y(n-1)-cy)*sen(wT)+cx
    Y(n)=(Y(n-1)-Cy)*cos(wT)+(X(n-1)-cx)*sen(wT)+cy
 */


#include "fisica3.h"


#include "fisica3.h"
#include "Personaje.h"
#include <math.h>

Fisica3::Fisica3(float x,float  y,float centrox,float centroy,float vel, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    posx=x;
    posy=y;
    cx=centrox;
    cy=centroy;
    w=vel;


    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/imagenes/arac.png");
    posSprite=0;
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(int(1000*T));
}


void Fisica3::move()
{

    float t=0.5*0.05;
    float aux,auxy;
    aux=posx-cx;
    auxy=posy-cy;
    posx=(aux)*cos(w*t)-(auxy)*sin(w*t)+cx;
    posy=(auxy)*cos(w*t)+(aux)*sin(w*t)+cy;
   // posx=posx+100;

    setPos(int(posx),int(posy));


    //Verificación de colisión del conejo con el fuego
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0; i < colliding_items.size(); ++i){
        if(typeid (*(colliding_items[i]))== typeid (Personaje)){

            emit estadoJuego(3);

            return;
        }
    }

}

//Margen de la imagen
QRectF Fisica3::boundingRect() const {

    return QRectF(0,0,122,150);
}

//Se dibuja el sprote asociado
void Fisica3::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,122, 150);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Fisica3::type() const
{
    return Type;
}
