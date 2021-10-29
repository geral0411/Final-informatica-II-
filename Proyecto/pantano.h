#ifndef PANTANO_H
#define PANTANO_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <Qtimer>

class pantano :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 12 };
    pantano(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

public slots:
    bool colision();
private:

    int posSprite;
    QPixmap sprite;

};


#endif // PANTANO_H
