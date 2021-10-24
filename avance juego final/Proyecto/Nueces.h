#ifndef NUECES_H
#define NUECES_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>


class Nueces : public QGraphicsItem
{

public:
    enum { Type = UserType + 3 };
    Nueces(QGraphicsItem *parent = 0);
    ~Nueces();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:

    int posSprite;
    QPixmap sprite;

};

#endif // NUECES_H
