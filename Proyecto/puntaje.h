#ifndef PUNTAJE_H
#define PUNTAJE_H

#include <QFont>
#include<QFontDatabase>

#include <QGraphicsTextItem>

class puntaje: public QGraphicsTextItem{
public:
    puntaje(int puntos,QGraphicsItem * parent=0);
    void incrementar(int cont);
    int getPuntaje();


private:
    int cont = 0;
};
#endif // PUNTAJE_H
