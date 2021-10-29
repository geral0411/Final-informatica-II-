#ifndef FISICA3_H
#define FISICA3_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QObject>



class Fisica3:  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum{ Type = UserType + 1};
    Fisica3(float  x, float  y,float centrox,float centroy,float vel,QGraphicsItem *parent= nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

    // variables y constantes para ecuación de mov circular:
    float  posy,posx;
    float  cx,cy;
    float  w; //velocidad angular de la particula(rad/s);
    float  T=0.05;//periodo

public slots:
    void move();

signals:
    void estadoJuego(int);

private:
    QPixmap sprite;
    QRectF Plataforma;
    int posSprite;
    int direccion;
    int inicioPos;
    int finPos;
};


#endif // FISICA3_H
