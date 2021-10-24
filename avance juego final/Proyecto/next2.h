#ifndef NEXT2_H
#define NEXT2_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

class Next2:  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum{ Type = UserType + 12};
    Next2(QGraphicsItem *parent= nullptr);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

public slots:
    void colision();
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

#endif // NEXT2_H
