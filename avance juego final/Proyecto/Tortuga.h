#ifndef TORTUGA_H
#define TORTUGA_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

class Tortuga:  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum{ Type = UserType + 9};
    Tortuga(int incio, int fin,QGraphicsItem *parent= nullptr);

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
#endif // TORTUGA_H
