#ifndef CASA_H
#define CASA_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

class casa : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    enum{ Type = UserType + 12};
    casa (QGraphicsItem *parent= nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    int heigth();

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

#endif // CASA_H
