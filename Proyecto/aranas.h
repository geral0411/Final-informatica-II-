#ifndef ARANAS_H
#define ARANAS_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <math.h>

class Aranas :  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum{ Type = UserType + 9};
    Aranas(int incio, int fin,QGraphicsItem *parent= nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
public slots:
    void nextSprite();

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

#endif // ARANAS_H
