/*
 Clase puntaje: muestra el puntaje en tiempo real.
 */

#include "puntaje.h"

puntaje::puntaje(int cont, QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    //cont=0;
    // dibujar el texto
    int id = QFontDatabase::addApplicationFont(":/CoinCount2.ttf");
    QFontDatabase::applicationFontFamilies(id);
    setPlainText(QString("") + QString::number(cont * 10));
    setDefaultTextColor(Qt::white);
    setFont(QFont("CoinCount2",40));
}

void puntaje::incrementar(int cont){
    cont++;
    setPlainText(QString("") + QString::number(cont * 10));

}

int puntaje::getPuntaje(){
    return cont;
}
