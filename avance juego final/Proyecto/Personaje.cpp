/*

 Clase Personaje: personaje principal, que posee movimientos de caminar a la derecha,
 izquierda , estar quieto, saltar y caer ,cada uno asociado a un estado.

 */


#include "Personaje.h"
#include <iostream>
#include <QDebug>

// se carga la imagen asociada, a si es un jugador o multijugador
void Personaje::friccion()
{
    float result = 0;
    result = Xo + n* Vo * cont * T - n*0.5 * Mk *9.8 * cont *cont *T*T;
    if(result-x() >=1 || result-x() <=-1){
        moveBy(result-x(),0);
        cont++;
    }

}

Personaje::Personaje(bool jugador, QGraphicsItem *parent) : QGraphicsItem(parent),m_StandingDirection(), mState(Standing){

    jugador_=jugador;
    setFlag(ItemClipsToShape);
    if(jugador_){
        mWalkPixmap = QPixmap(":/imagenes/Ardilla.png");
        mStandingPixmap = QPixmap(":/imagenes/Ardilla.png");
        mJumpPixmap = QPixmap(":/imagenes/Ardilla.png");
        standShootPixmap = QPixmap(":/imagenes/Ardilla.png");
        mPixmap = mWalkPixmap;
    }
    else{
        mWalkPixmap = QPixmap(":/imagenes/Ardilla.png");
        mStandingPixmap = QPixmap(":/imagenes/Ardilla.png");
        mJumpPixmap = QPixmap(":/imagenes/Ardilla.png");
        standShootPixmap = QPixmap(":/imagenes/Ardilla.png");
        mPixmap = mWalkPixmap;
    }
    time = new QTimer;
    connect(time,SIGNAL(timeout()),this,SLOT(friccion()));
    time->start(T*1000);
}

Personaje::~Personaje(){

}

//Para cuando el personaje está quieto
void Personaje::stand(){

    mPixmap = mStandingPixmap;
    mCurrentFrame = 0;
    mState = Standing;
}

//Para cuando el conejo está saltando
void Personaje::jump(){
    mState = Jumping;
}

//Para cuando el personaje  está caminando
void Personaje::walk(){

    if(mState == Walking) {
        return;
    }

    mPixmap = mWalkPixmap;
    mCurrentFrame = 0;
    mState = Walking;

}

//Para cuando el personaje está cayendo
void Personaje::fall(){

    mState = Falling;
}

bool Personaje::isFalling(){

    return mState == Falling;
}

int Personaje::wid()
{
    return mPixmap.width(); // retorna el ancho
}

void Personaje::new_spike(float x, float v, float mg, int p)
{
    Xo = x;
    Vo = v;
    Mk = mg;
    n = p;
    cont = 1;
}


//retorna la direccion de conejo
int Personaje::direction() const{

    return m_direction;
}

int Personaje::standingDirection() const{

    return m_StandingDirection;
}

//Cambia el sprite del personaje
void Personaje::nextFrame(){

    mCurrentFrame += 70;

    if (mCurrentFrame >= 567 ) {
        mCurrentFrame = 0;
    }
}

void Personaje::set_m_direction(int mdirection)
{
    m_direction=mdirection;
}

//Define la margen del objeto
QRectF Personaje::boundingRect() const{

    return QRectF(0,0,70,70);
}

//Se dibuja el objeto en la escena a partir del sprite
void Personaje::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,70, 70);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

// se cambia la direccín del personaje
void Personaje::addDirection(int direction){

    if (direction == m_direction)
        return;

    m_direction += direction;

    if (0 != m_direction){
        if (-1 == m_direction) setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        else setTransform(QTransform());
    }
}

void Personaje::addStandingDirection(int standingDirection){

    m_StandingDirection = standingDirection;
}

//Verifica cuando el personaje está tocando con los pies un objeto
bool Personaje::isTouchingFoot(QGraphicsItem *item){

    //return collidesWithItem(item);
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

//Verifica cuando el personaje está tocando con la cabeza un objeto
bool Personaje::isTouchingHead(QGraphicsItem *item){

    //return collidesWithItem(item);
    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

//Verifica cuando el personaje está tocando alguna de las plataformas
bool Personaje::isTouchingPlatform(QGraphicsItem *item){
    //return collidesWithItem(item);
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}


