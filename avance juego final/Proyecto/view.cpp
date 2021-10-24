/*

 Clase View: permite apaganr las barras del scroll y mostrar al inicio ,
 la escena en pantalla.
 */

#include "view.h"

View::View() {

    this->setFixedSize(QSize(1280, 720));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void View::sceneSet(QGraphicsScene *scene) {

    setScene(scene);
    emit sceneChanged();
}
