#ifndef INICIO_H
#define INICIO_H


#include <QPushButton>
#include <QLineEdit>
#include <string>
#include "mainwindow.h"
#include "mundos.h"
#include "view.h"
#include "login.h"

using namespace std;

class View;
class Mundos;

class Inicio: public QGraphicsScene{
    Q_OBJECT
public:
    Inicio(View *view, QWidget *parent = 0);
    string lectura_txt(string name);
    bool checkUser();

signals:
    void sceneChanged();


private slots:
     void multijugadorLogin();
     void unjugadorLogin();
     void newUser();

private:
    int selection = 0;
    const int width = 1280;
    const int height = 720;
    bool usuario=false;
    string database;
    View *viewer;
    QGraphicsPixmapItem *foreground;
    login *loginWindow;

    QScrollBar *scroll;
    Mundos *scene;
    QPushButton *multijugador;
    QPushButton *Unjugador;
    QPushButton *newUserButton;
    QLineEdit *labelusuario;
    QLineEdit *labelcontrasena;
    QLabel *userName;
    QLabel *password;
    QGraphicsView *view;

};
#endif // INICIO_H
