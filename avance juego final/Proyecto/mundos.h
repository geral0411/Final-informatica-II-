#ifndef MUNDOS_H
#define MUNDOS_H

#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QAbstractAnimation>
#include <QDebug>
#include <QGraphicsView>
#include <QList>
#include <QScrollBar>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

#include "Tortuga.h"
#include "fondo.h"
#include "aranas.h"
#include "muros.h"
#include "murosnota.h"
#include "Nueces.h"
#include "Personaje.h"
#include "puntaje.h"
#include "vidas.h"
#include "halcon.h"
#include "roca.h"
#include "next.h"
#include "gameover.h"

#include "next2.h"
#include "triunfo.h"


class Mundos :public QGraphicsScene
{

    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)
public:
    explicit Mundos (bool configurar,QScrollBar *s,QObject *parent = nullptr);
    ~Mundos();
    qreal jumpFactor() const;
    void setJumpFactor(const qreal &jumpFactor);
    void iniciarEscenaUno();
    void iniciarEscenaDos();
    void reiniciarEscenaUno();
    void reiniciarEscenaDos();
    void Borrarmundo1();


private:
    void checkTimer();


private slots:
    void jumpPersonaje();
    void jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
    void moverPersonaje();
    void fallPersonaje();
    bool manejoColisiones();
    void checkColisionMuros();
    void checkColNueces();
    void Estado(int n);
    QGraphicsItem *collidingPlatforms();


protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    void jumpFactorChanged(qreal);


private:
    int anchoEscena=6600;
    int direction;
    bool reinicio=false;
    bool quieto=false;
    bool Jugador=true;
    bool configurar_=true;
    bool mundo;

    Personaje *per;

    Fondo *background=0;
    Fondo *ground;
    Fondo *danger;
    Fondo *LogoPuntaje;
    Fondo *LogoVida;

    puntaje *Puntaje;
    vidas *vidas_;

    qreal minX;
    qreal maxX;
    qreal nivelTierra;
    qreal posicionX;
    int coeficiente=7;
    int desplazamientoMundo=0;
    int Vida=0;

    QTimer *timer;
    QTimer *mFallTimer;
    QPropertyAnimation *m_jumpAnimation;
    qreal m_jumpFactor;
    int m_jumpHeight=200;

    Halcon *Halcon1;
    Halcon *Halcon2;
    Halcon *Halcon3;
    Roca *roca;
    Next *flag;
    Next2 *zanahoriaDorada;

    QGraphicsItem *m_platform;

    Tortuga *Tortuga1;
    Tortuga *Tortuga2;
    Tortuga *Tortuga3;
    Tortuga *Tortuga4;
    Tortuga *Tortuga5;
    Tortuga *Tortuga6;
    Tortuga *Tortuga7;


    QScrollBar *scroll;
    GameOver *gameOverWindow;
    Triunfo *ganar;
    QGraphicsView *view;


    //complementos de la escena

    QList <Nueces *> nueces;
    QList <MurosNota*> ladrillosNota;
    QList <Muros*> muro;
    QList <Tortuga*> cerdo;
    QList<Nueces *> eliminarnueces(QList<Nueces *>nueces,int pos);


};

#endif // MUNDOS_H