#ifndef PERSONAJE_H
#define PERSONAJE_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTransform>
#include <QTimer>
#include <QObject>

class Personaje : public QObject, public QGraphicsItem
{
Q_OBJECT
public slots:

    void friccion();

public:
     Personaje(bool jugador,QGraphicsItem *parent = 0);
     ~Personaje();
    int direction() const;
    int standingDirection() const;
    void addStandingDirection(int standingDirection);
    void addDirection(int direction);
    void nextFrame();
    void set_m_direction(int mdirection);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool isTouchingFoot(QGraphicsItem *item);
    bool isTouchingHead(QGraphicsItem *item);
    bool isTouchingPlatform(QGraphicsItem *item);

    void stand();
    void jump();
    void standShoot();
    void walk();
    void fall();
    bool isFalling();
    int wid ();
    void new_spike(float x, float v, float mg,int p);



private:
    enum State {
         Standing = 0,
         Walking,
         Jumping,
         Falling
    };

    int m_direction=0;
    int mCurrentFrame=0;
    int m_StandingDirection;
    bool jugador_;
    State mState;
    QPixmap mPixmap;
    QPixmap mWalkPixmap;
    QPixmap mStandingPixmap;
    QPixmap mJumpPixmap;
    QPixmap standShootPixmap;
    QTimer *time;
    float Xo = 0;
    float Vo = 0;
    float Mk = 0;//coeficiente de friccion
    int cont = 0;
    float T = 0.1;//tiempo de muestreo
    int n = 0;

};

#endif // PERSONAJE_H
