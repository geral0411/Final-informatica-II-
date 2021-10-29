/*


 Clase Mainwindow: ventana principal desde donde se adminsitra el inicio del juego

 */

#include "mainwindow.h"
#include <iostream>


MainWindow::MainWindow()
{

    createScene();
    setCentralWidget(view);
    setWindowTitle("La Ardilla lulu");
}

void MainWindow::closeEvent(QCloseEvent *){

    qApp->quit();
}

void MainWindow::createScene(){

    view = new View;
    title = new Inicio(view);
}

void MainWindow::setSize(){

    this->setFixedSize(1280,740);
    this->move(0, 0);
}
