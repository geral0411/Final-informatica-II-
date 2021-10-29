/*


 Clase Halcon: enemigo del mundo 3

 */

#include "halcon.h"
#include "roca.h"
#include "Personaje.h"

//Costructor donde se carga la imagen y se inicia el timer asociado
Halcon::Halcon(int inicio,int fin,QGraphicsItem *parent) : QGraphicsItem(parent)
{
    inicioPos=inicio;
    finPos=fin;
    direccion = 1;
    setFlag(ItemClipsToShape);
    sprite = QPixmap(":/imagenes/halcon.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextSprite()));
    timer->start(100);


}

//Variación del sprite que esta asociada al timer(SLOT)
void Halcon::nextSprite()
{

    //Manejo de Sprites
    //Distancia en caada sprite
    posx=x();
    posSprite += 129;
    //Condicion volver al primer sprite, si sobre pasa la dimension la imagen plana
    if(posSprite >= 514)
    {
        posSprite = 0;
    }
    if(this->pos().x() < inicioPos|| this->pos().x() > finPos) {//movimiento
        direccion = -direccion;
        setTransform(QTransform(-direccion, 0, 0, 1, boundingRect().width(), 0));

    }
    setPos(this->pos().x() + (direccion*7), this->pos().y());
    //crea la roca
    if((posx<=350)||((posx>=300) && (posx<=700))||((posx>=700) && (posx<=1100))||((posx>=1100) && (posx>=1500))
    ||((posx>=1500) && (posx<=1900)))
    {
       if(f==false){
            f=true;
            tirar_roca();
            roca->var=1;}


        if (roca->var==0){
            scene()->removeItem(roca);
            tirar_roca();
            roca->var=1;
        }
        if(roca->colis==true){
            emit estadoJuego(6);
            roca->colis=false;
        }

    }

}

//Se agrega la roca a la escena
void Halcon::tirar_roca()
{

      if(direccion==-1){
         roca= new Roca(pos().x()+ (direccion*7)+200);
         roca->setPos(this->pos().x()+ (direccion*7)+200,150);
         roca->direccion=direccion;
      }
      else{
          roca= new Roca(pos().x()+ (direccion*7));
          roca->setPos(this->pos().x()+ (direccion*7),150);
      }

      scene()->addItem(roca);

}

//Margen del objeto
QRectF Halcon::boundingRect() const {

    return QRectF(0,0,122,150);
}

//Se dibuja el objeto en la escena a partir del sprite
void Halcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, sprite, posSprite, 0,122, 150);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget)
    Q_UNUSED(option)
}

int Halcon::type() const
{
    return Type;
}

