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
#include "casa.h"
#include "pantano.h"

#include "next2.h"
#include "triunfo.h"
#include "fisica3.h"


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
    void iniciarEscenaTres();
    void reiniciarEscenaUno();
    void reiniciarEscenaDos();
    void reiniciarEscenaTres();
    void Borrarmundo1();
    void Borrarmundo2();


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
   // void checkcolpant();
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
    bool Escenario_final= false;
    int puntos = 0;
    bool mundo1 = false;

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

    Roca *roca;
    Next *next;
    Next2 *next2;
    casa *final;

    QGraphicsItem *m_platform;

    Halcon *halcon[9];
    Tortuga *tortuga[10];
    Aranas *aranas[10];
    //pantano *pant[5];

    pantano *pant[4];


    Fisica3 *aranita1;
    Fisica3 *aranita2;

    QScrollBar *scroll;
    GameOver *gameOverWindow;
    Triunfo *ganar;
    QGraphicsView *view;

    //complementos de la escena

    QList <Nueces *> nueces;
    QList <MurosNota*> ladrillosNota;
    QList <Muros*> muro;
    QList<Nueces *> eliminarnueces(QList<Nueces *>nueces,int pos);


};

#endif // MUNDOS_H
