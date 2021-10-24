#include "mundos.h"
#include <iostream>

// se inicializan los timer y se hace un llamado al metodo que inicaliza la escena uno
Mundos::Mundos(bool configurar, QScrollBar *s,QObject *parent):QGraphicsScene(0,0,8000,720,parent)
  , m_jumpAnimation(new QPropertyAnimation(this))
  , m_platform()
  , scroll(s)

{

    configurar_=configurar;
    Vida=5;
    iniciarEscenaUno();

    //inicializamos timer asociado al mov del personaje
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moverPersonaje()));
    timer->setInterval(20);

    mFallTimer = new QTimer(this);
    connect(mFallTimer,SIGNAL(timeout()),this,SLOT(fallPersonaje()));
    mFallTimer->setInterval(20);

    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);

    connect(this, &Mundos::jumpFactorChanged, this, &Mundos::jumpPersonaje);
    connect(m_jumpAnimation, &QPropertyAnimation::stateChanged, this, &Mundos::jumpStatusChanged);

    per->addStandingDirection(1);

}

//Verifica si se oprime alguna de las teclas asociada al movimiento asigna la dirección y chequea el timer asociado al desplazamiento
void Mundos::keyPressEvent(QKeyEvent *event){
    if (event->isAutoRepeat()){
        return;
    }

    switch (event->key()){
        case Qt::Key_Right:
        {
            reinicio=true;
            per->addDirection(1);
            per->addStandingDirection(1);
            checkTimer();
            break;
        }


        case Qt::Key_Left:
        {
            reinicio=false;
            per->addDirection(-1);
            per->addStandingDirection(-1);
            checkTimer();
            break;
        }

        case Qt::Key_Space:
        {
            if(mFallTimer->isActive()){
                return;
            }
            else{
                if (QAbstractAnimation::Stopped == m_jumpAnimation->state()){
                    m_jumpAnimation->start();

                }
            }
            break;
        }

        default:
            break;
        }

}

//Verifica si se oprime alguna de las teclas asociada al movimiento y modifca el direccionamiento del conejo con el fin de que
//el desplazamiento solo ocurra una vez , es decir para el timer, hasta que ocurra un nuevo evento.
void Mundos::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()){
        return;
    }

    switch (event->key())
    {
        case Qt::Key_Right:
            {
                reinicio=true;
                per->addDirection(-1);
                per->addStandingDirection(1);
                checkTimer();
                break;
            }

        case Qt::Key_Left:
            {
            reinicio=false;
            per->addDirection(1);
            per->addStandingDirection(-1);
            checkTimer();
            break;
            }

        default:
            break;
    }

}

//se da el movimento al perosnaje según el evento y a su vez se desplaza la escena
void Mundos::moverPersonaje()
{
    if (mundo){
        checkColisionMuros();
        checkColNueces();
    }

    int dx;
    if(per->isFalling()){
        return;
    }

    per->nextFrame();


    direction = per->direction();

    if (0 == direction) return;

    if(!(m_platform && per->isTouchingPlatform(m_platform))&& m_jumpAnimation->state() == QAbstractAnimation::Stopped){
        if(m_platform){
            per->fall();
            mFallTimer->start();
        }
    }



    dx = direction * coeficiente;
    if (direction > 0){

        if(per->pos().x()==8100){
            return;
        }
        per->moveBy(dx, 0);
        int diff = per->pos().x() - scroll->value();

        if(diff > 850){
            scroll->setValue(dx + scroll->value());
            background->setPos(dx + background->pos().x(), background->y());
            Puntaje->setPos(dx + Puntaje->pos().x(), Puntaje->y());
            LogoPuntaje->setPos(dx + LogoPuntaje->pos().x(), LogoPuntaje->y());
            vidas_->setPos(dx + vidas_->pos().x(), vidas_->y());
            LogoVida->setPos(dx + LogoVida->pos().x(), LogoVida->y());
        }
    }

    if (direction < 0){

        if(per->pos().x()<0){
            return;
        }

        per->moveBy(dx, 0);
        int diff = per->pos().x() - scroll->value();

        if(diff < 600){

            if(background->pos().x() == 0){
                return;
            }

            scroll->setValue(dx + scroll->value());
            background->setPos(dx + background->pos().x(), background->y());
            Puntaje->setPos(dx + Puntaje->pos().x(), Puntaje->y());
            LogoPuntaje->setPos(dx + LogoPuntaje->pos().x(), LogoPuntaje->y());
            vidas_->setPos(dx + vidas_->pos().x(), vidas_->y());
            LogoVida->setPos(dx + LogoVida->pos().x(), LogoVida->y());

        }
    }

}


void Mundos::jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    if(newState == QAbstractAnimation::Stopped && oldState == QAbstractAnimation::Running){
    }
}

//verifica la caida del personaje
void Mundos::fallPersonaje()
{

    per->setPos(per->pos().x(), per->pos().y() +30);
    QGraphicsItem *item = collidingPlatforms();
    if(item && manejoColisiones()){
       mFallTimer->stop();
       per->walk();
    }
    else if(per->pos().y() + per->boundingRect().height() >= nivelTierra){
            per->setPos(per->pos().x(), nivelTierra - per->boundingRect().height());
            mFallTimer->stop();
            per->walk();
            m_platform = 0;
        }
}

//verifica el salto del personaje
void Mundos::jumpPersonaje()
{
    if (QAbstractAnimation::Stopped == m_jumpAnimation->state()){
       per->stand();
       return;
    }
    QGraphicsItem *item = collidingPlatforms();
    if(item){
        if(per->isTouchingHead(item)){

            m_jumpAnimation->stop();

            if(m_platform){
                per->setPos(per->pos().x(), m_platform->pos().y() - per->boundingRect().height());
                return;
            }
            if(!m_platform){
                per->setPos(per->pos().x(), nivelTierra - per->boundingRect().height());
                return;
            }
        }
        else{
            if(manejoColisiones()){
                return;
            }
        }
    }

    if(mFallTimer->isActive()){
        return;
    }
    qreal y = (nivelTierra - per->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
    if(m_platform){
        y = (m_platform->pos().y() - per->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
        if(!(m_platform && per->isTouchingPlatform(m_platform)) && m_jumpFactor < 0.1 ) {
            if((per->pos().x() < m_platform->pos().x()) || (per->pos().x() > m_platform->pos().x() + m_platform->boundingRect().width())){
                if(!m_platform){
                    m_platform = 0;
                }
                if(per->pos().y() <nivelTierra){
                    per->fall();
                    mFallTimer->start();
                    return;
                }
            }
        }
    }
    per->setPos(per->pos().x(), y);
}

void Mundos::iniciarEscenaUno()
{
    mundo=true;
    setSceneRect(0,0,8000,720);
    nivelTierra = 660;



    //Ponemos posicion incial del cielo
    background=new Fondo(QPixmap(":/imagenes/fondo.png"));
    background->setPos(0,0);
    addItem(background);


    //add ground
    ground = new Fondo(QPixmap(":/imagenes/suelo.png"));
    ground->setPos(0,nivelTierra);
    addItem(ground);

    //se agrega puntaje
    LogoPuntaje = new Fondo(QPixmap(":/imagenes/puntaje.png"));
    LogoPuntaje->setPos(870, nivelTierra -647 );
    addItem(LogoPuntaje);
    Puntaje = new puntaje();
    Puntaje->setPos(980, nivelTierra - Puntaje->boundingRect().height()-610);
    addItem(Puntaje);

    //Se agrega vidas
    LogoVida = new Fondo(QPixmap(":/imagenes/vidastxt.png"));
    LogoVida->setPos(200, nivelTierra - 647 );
    addItem(LogoVida);

    vidas_ = new vidas(Vida);
    Vida--;
    vidas_->setPos(330, nivelTierra - vidas_->boundingRect().height()-610);
    addItem(vidas_);


    //AgregarPersonaje
    per = new Personaje(Jugador);
    per->setPos(50, nivelTierra - per->boundingRect().height() );
    addItem(per);

    //Se verifica la opcion de multijugador
    if(configurar_){
        Jugador=true;
    }
    else Jugador=!Jugador;



    startTimer( 100 );


    //Agregamos ladrillos
    int posLadrillo[50][3] = {{400,500,2}, {526,400,2}, {650,300,2}, {900,400,1},{1100,400,1},{1240,300,2}, {1366,450,2}, {1600,520,8}, {1740,330,1}, {1920,330,1}
                             , {2100,200,3}, {2300,460,4}, {2800,615,2}, {2800,575,2}, {2800,535,2},{3100,615,2}, {3100,575,2}, {3360,400,1}, {3800,615,2}
                             , {3800,575,2},{3800,535,2}, {4050,350,1}, {4250,200,1}, {4400,615,2}, {4400,575,2}, {4400,535,2}, {4400,495,2}, {4400,455,2}
                             , {4400,415,2}, {4400,375,2}, {4920,480,6}, {5000,300,1},{5100,200,1},{5600,615,2}, {5680,570,2},{5760,525,2},{5840,480,2}, {5920,435,2}
                             , {6500,450,1},{7000,450,1},{7500,480,1},{7600,615,2},{7600,575,2},{7600,535,2},{7600,495,2},{7600,455,2},{7600,415,2},{7600,375,2},{7600,335,2},{7600,295,2}};
    for (int i = ladrillosNota.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillosNota.at(i));
    }
    ladrillosNota.clear();
    for (int i = 0; i < 50; i++)
    {
        ladrillosNota.append(new MurosNota(posLadrillo[i][2]));
        ladrillosNota.last()->setPos(posLadrillo[i][0],posLadrillo[i][1]);
        addItem(ladrillosNota.last());
    }


  //  Agregamos nueces
    int posNueces[40][2] ={{800,600},{850,600},{900,600},{950,600},{1000,600},{1050,600},{1100,600},{1150,600},{1200,600}, {900,340}
                             ,{1100,340},{1610,460},{1660,460},{1710,460},{1760,460},{1810,460},{1860,460},{1910,460},{1960,460},{2010,460}
                              ,{2060,460},{2100,140},{2150,140},{2200,140},{2250,140},{2350,600},{2400,600},{2450,600},{3300,600},{3400,600}
                             ,{5110,140},{5010,240},{4950,600},{5000,600},{5050,600},{5100,600},{5150,600},{5200,600},{3300,600},{3350,600}};
    for (int i = nueces.size() - 1; 0 <= i; i--)
    {
        removeItem(nueces.at(i));
    }
    nueces.clear();

    for (int i= 0; i < 40;i++)
    {
        nueces.append(new Nueces());
        nueces.last()->setPos(posNueces[i][0], posNueces[i][1]);
        addItem(nueces.last());

    }


     //Agregamos los tortugas enemigas
      Tortuga1 = new Tortuga(800,1200);
      Tortuga1->setPos(1200, nivelTierra-100);
      addItem(Tortuga1);
      connect(this->Tortuga1, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      Tortuga2 = new Tortuga(1600,1900);
      Tortuga2->setPos(1900, nivelTierra-230);
      addItem(Tortuga2);
      connect(this->Tortuga2, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      Tortuga3 = new Tortuga(2100,2400);
      Tortuga3->setPos(2400, nivelTierra-100);
      addItem(Tortuga3);
      connect(this->Tortuga3, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      Tortuga4 = new Tortuga(3250,3500);
      Tortuga4->setPos(3500, nivelTierra-100);
      addItem(Tortuga4);
      connect(this->Tortuga4, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      Tortuga5 = new Tortuga(3950,4100);
      Tortuga5->setPos(4100, nivelTierra-100);
      addItem(Tortuga5);
      connect(this->Tortuga5, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      Tortuga6 = new Tortuga(4900,5300);
      Tortuga6->setPos(5300, nivelTierra-100);
      addItem(Tortuga6);
      connect(this->Tortuga6, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      Tortuga7= new Tortuga(4900,5100);
      Tortuga7->setPos(5100, nivelTierra-270);
      addItem(Tortuga7);
      connect(this->Tortuga7, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));


      //Agregamos Halcones
        Halcon1=new Halcon(6000,6400);
        Halcon1->setPos(6000,50);
        addItem(Halcon1);
        connect(this->Halcon1, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

        Halcon2=new Halcon(6500,6900);
        Halcon2->setPos(6500,50);
        addItem(Halcon2);
        connect(this->Halcon2, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

        Halcon3=new Halcon(7000,7400);
        Halcon3->setPos(7000,50);
        addItem(Halcon3);
        connect(this->Halcon3, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));


        //Agrego bandera fin de primer nivel
        flag=new Next();
        flag->setPos(7500,400);
        //flag->setPos(400,550);
        addItem(flag);
        connect(this->flag, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

}

void Mundos::iniciarEscenaDos()
{
    mundo=false;
    setSceneRect(0,0,8000,720);
    nivelTierra = 660;

    //Ponemos posicion incial del cielo
    background=new Fondo(QPixmap(":/imagenes/fondo_escena2.png"));
    background->setPos(0,0);
    addItem(background);


    //add ground
    ground = new Fondo(QPixmap(":/imagenes/suelo.png"));
    ground->setPos(0,nivelTierra);
    addItem(ground);

    //se agrega puntaje
    LogoPuntaje = new Fondo(QPixmap(":/imagenes/puntaje.png"));
    LogoPuntaje->setPos(870, nivelTierra -647 );
    addItem(LogoPuntaje);
    Puntaje = new puntaje();
    Puntaje->setPos(980, nivelTierra - Puntaje->boundingRect().height()-610);
    addItem(Puntaje);

    //Se agrega vidas
    LogoVida = new Fondo(QPixmap(":/imagenes/vidastxt.png"));
    LogoVida->setPos(200, nivelTierra - 647 );
    addItem(LogoVida);

    vidas_ = new vidas(Vida);
    Vida--;
    vidas_->setPos(330, nivelTierra - vidas_->boundingRect().height()-610);
    addItem(vidas_);


    //AgregarPersonaje
    per = new Personaje(Jugador);
    per->setPos(50, nivelTierra - per->boundingRect().height() );
    addItem(per);
    if(configurar_){
        Jugador=true;

    }
    else Jugador=!Jugador;


    startTimer( 100 );


    //Agregamos ladrillos
    int posLadrillo[40][3] = { {1150,615,2}, {1150,575,2}, {1150,535,2},{1150,495,2},{1150,455,2}, {2600,620,2}
                             , {3500,615,2}, {3500,575,2}, {3500,535,2},{3500,495,2},{3500,575,2}, {3500,535,2}
                             , {4350,615,2}, {4350,575,2}, {4350,535,2},{4350,495,2},{4350,455,2}, {4350,415,2}
                             , {4350,375,2}, {5600,615,2}, {5680,570,2},{5760,525,2},{5840,480,2}, {5920,435,2}
                             , {7500,420,1}, {7600,615,2}, {7600,575,2},{7600,535,2},{7600,495,2}, {7600,455,2}
                             , {7600,415,2}, {7600,375,2}, {7600,335,2},{7600,295,2},{7600,255,2}, {7600,215,2}
                             , {7600,175,2}, {7600,135,2}, {7600,95,2},{7600,55,2}};
    for (int i = ladrillosNota.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillosNota.at(i));
    }
    ladrillosNota.clear();
    for (int i = 0; i < 40; i++)
    {
        ladrillosNota.append(new MurosNota(posLadrillo[i][2]));
        ladrillosNota.last()->setPos(posLadrillo[i][0],posLadrillo[i][1]);
        addItem(ladrillosNota.last());
    }
    //Agregamos muros 2
    int posMuro[12][3] = {{400,500,1}, {850,500,1}, {1550,500,3}, {1680,330,1},{2230,500,7}
                          ,{3750,400,1},{4050,400,1},{4750,480,1},{5000,350,1},{5250,480,1},{6100,240,1},{7200,240,1}};
    for (int i = muro.size() - 1; 0 <= i; i--)
    {
        removeItem(muro.at(i));
    }
    muro.clear();
    for (int i = 0; i < 12; i++)
    {
        muro.append(new Muros(posMuro[i][2]));
        muro.last()->setPos(posMuro[i][0],posMuro[i][1]);
        addItem(muro.last());
    }



/*
     //Agregamos los jabali´s enemigos
      jabali1 = new JabaliEnemigo(300,700);
      jabali1->setPos(300, nivelTierra-100);
      addItem(jabali1);
      connect(this->jabali1, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));


      jabali2 = new JabaliEnemigo(700,1000);
      jabali2->setPos(700, nivelTierra-100);
      addItem(jabali2);
      connect(this->jabali2, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      jabali3 = new JabaliEnemigo(1650,1800);
      jabali3->setPos(1650, nivelTierra-250);
      addItem(jabali3);
      connect(this->jabali3, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      jabali4 = new JabaliEnemigo(1550,1950);
      jabali4->setPos(1550, nivelTierra-100);
      addItem(jabali4);
      connect(this->jabali4, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      jabali5 = new JabaliEnemigo(2900,3400);
      jabali5->setPos(2900, nivelTierra-100);
      addItem(jabali5);
      connect(this->jabali5, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      jabali6 = new JabaliEnemigo(3700,4250);
      jabali6->setPos(3700, nivelTierra-100);
      addItem(jabali6);
      connect(this->jabali6, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      jabali7 = new JabaliEnemigo(4600,4950);
      jabali7->setPos(4600, nivelTierra-100);
      addItem(jabali7);
      connect(this->jabali7, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      jabali8 = new JabaliEnemigo(5110,5400);
      jabali8->setPos(5110, nivelTierra-100);
      addItem(jabali8);
      connect(this->jabali8, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

*/

      //Agregamos zanahoria de fin de segundo nivel
      zanahoriaDorada = new Next2();
      zanahoriaDorada->setPos(7480,390);
      //zanahoriaDorada->setPos(400,550);
      addItem(zanahoriaDorada);
      connect(this->zanahoriaDorada, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      timer = new QTimer(this);
      connect(timer,SIGNAL(timeout()),this,SLOT(moverPersonaje()));
      timer->setInterval(20);
      mFallTimer = new QTimer(this);
      connect(mFallTimer,SIGNAL(timeout()),this,SLOT(fallPersonaje()));
      mFallTimer->setInterval(20);

      per->set_m_direction(0);
      per->addDirection(1);
}

qreal Mundos::jumpFactor() const{

    return m_jumpFactor;
}

void Mundos::setJumpFactor(const qreal &jumpFactor)
{
        if (m_jumpFactor == jumpFactor) return;

        m_jumpFactor = jumpFactor;
        emit jumpFactorChanged(m_jumpFactor);
}

//verifica el estado del timer asociado al movimiento del personaje
void Mundos::checkTimer()
{

    if (0 == per->direction()){
        per->stand();
        timer->stop();
    }
    else if (!timer->isActive()){
        timer->start();
        per->walk();
    }

}

//verifica la colision con los muros en la parte superior e inferior
QGraphicsItem *Mundos::collidingPlatforms()
{
        QList<QGraphicsItem*> items =  collidingItems(per);
        foreach(QGraphicsItem *item, items){
            if(MurosNota *brickplatform = qgraphicsitem_cast<MurosNota *>(item)){
                return brickplatform;
            }
            if(Muros *murito = qgraphicsitem_cast<Muros *>(item)){
                return murito;

           }
        }
        return 0;
}

//------------- en esta sección se verifican todas las colisiones------------------------
bool Mundos::manejoColisiones()
{
    {
    QGraphicsItem *platform= collidingPlatforms();
    if(platform) {
        QPointF platformPos = platform->pos();
        if(per->isTouchingFoot(platform)){
            per->setPos(per->pos().x(), platformPos.y() - per->boundingRect().height());
            m_platform = platform;
            m_jumpAnimation->stop();
            return true;
        }
    }
    else{
        m_platform = 0;
    }
    return false;
    }
    return 0;
}

void Mundos::checkColisionMuros()
{
    QList<QGraphicsItem*> items = collidingItems(per);
    foreach (QGraphicsItem* item, items) {

        MurosNota * w = qgraphicsitem_cast<MurosNota *>(item);
        if(w){
            if(w->pos().x()){
                if(per->pos().x() < w->pos().x())
                    per->setPos(w->pos().x()- per->boundingRect().width(),per->pos().y());
                if(per->pos().x() > w->pos().x())
                {
                    per->setPos(w->pos().x() + per->boundingRect().width()+63,per->pos().y());
                }
            }
        }
    }
}


void Mundos::checkColNueces()
{
    for (int i=0;i<nueces.size() ;i++ ) {
         if(per->collidesWithItem(nueces.at(i))){
            removeItem(nueces.at(i));
            Puntaje->incrementar();
            nueces=eliminarnueces(nueces,i);

         }
    }
}


//se elimina la zanahoria una vez colisionada
QList<Nueces *> Mundos::eliminarnueces(QList<Nueces *> nueces, int pos)
{
    QList<Nueces *> aux;
    for (int i=0;i<nueces.size() ;i++ ) {
        if (i!=pos){
            aux.push_back(nueces.at(i));
        }
    }
    return aux;

}

//Se ejecuta una acción cuando ocurre las diferentes colisiones con los enemigos o banderas, a partir de las señales
//emitidas por cada uno de ellos, asociadas a un timer
void Mundos::Estado(int n)
{
    int number = n;
    if(number == 0){
        if(configurar_){
            Jugador=true;

        }
        else Jugador=!Jugador;
       Borrarmundo1();
       iniciarEscenaDos();
    }
    else if(number == 1){
        if (Vida==0){
            reiniciarEscenaUno();
            gameOverWindow = new GameOver();
            gameOverWindow->setWindowFlags(((gameOverWindow->windowFlags()|Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
            gameOverWindow->exec();
        }
        else reiniciarEscenaUno();
    }
    else if(number==2){
        if (Vida==0){
            reiniciarEscenaDos();
            gameOverWindow = new GameOver();
            gameOverWindow->setWindowFlags(((gameOverWindow->windowFlags()|Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
            gameOverWindow->exec();
        }
        else reiniciarEscenaDos();

    }
    else if(number==3){
        if (Vida==0){
            reiniciarEscenaDos();
            gameOverWindow = new GameOver();
            gameOverWindow->setWindowFlags(((gameOverWindow->windowFlags()|Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
            gameOverWindow->exec();
        }
        else reiniciarEscenaDos();

    }
    else if(number == 4){
        reiniciarEscenaDos();
        ganar = new Triunfo();
        ganar->setWindowFlags(((ganar->windowFlags()|Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
        ganar->exec();
    }
    else return;
}

//se eliminan los objetos del primer mundo y se vuelven a inicializar los timer y direccionamiento del personaje
void Mundos::reiniciarEscenaUno()
{
    delete per;
    delete flag;
    delete timer;
    delete mFallTimer;
    delete background;
    delete ground;
    delete danger;
    delete Puntaje;
    delete LogoPuntaje;
    delete LogoVida;
    delete Tortuga1;
    delete Tortuga2;
    delete Tortuga3;
    delete Tortuga4;
    delete Tortuga5;
    delete Tortuga6;
    delete Tortuga7;
    delete Halcon1;
    delete Halcon2;
    delete Halcon3;
    m_platform=0;
    m_jumpAnimation->stop();
    scroll->setValue(0);
    iniciarEscenaUno();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moverPersonaje()));
    timer->setInterval(20);
    mFallTimer = new QTimer(this);
    connect(mFallTimer,SIGNAL(timeout()),this,SLOT(fallPersonaje()));
    mFallTimer->setInterval(20);
    if(reinicio){
        per->set_m_direction(0);
        per->addDirection(1);
    }
    else {

        per->set_m_direction(0);
        per->addDirection(-1);
    }

}

//se eliminan los objetos del segundo mundo y se vuelven a inicializar los timer y direccionamiento del personaje
void Mundos::reiniciarEscenaDos()
{
    delete per;
    delete timer;
    delete zanahoriaDorada;
    delete mFallTimer;
    delete background;
    delete ground;
    delete danger;
    delete Puntaje;
    delete LogoPuntaje;
    delete LogoVida;


    m_platform=0;
    m_jumpAnimation->stop();
    scroll->setValue(0);
    iniciarEscenaDos();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moverPersonaje()));
    timer->setInterval(20);
    mFallTimer = new QTimer(this);
    connect(mFallTimer,SIGNAL(timeout()),this,SLOT(fallPersonaje()));
    mFallTimer->setInterval(20);
    if(reinicio){
        per->set_m_direction(0);
        per->addDirection(1);
    }
    else {

        per->set_m_direction(0);
        per->addDirection(-1);
    }

}

// se eliminan los objetos del primer mundo y se inicializan el valor del scroll y la plataforma
void Mundos::Borrarmundo1()
{
    delete per;
    delete timer;
    delete mFallTimer;
    delete background;
    delete ground;
    delete danger;
    delete Puntaje;
    delete flag;
    delete LogoPuntaje;
    delete LogoVida;
    delete Tortuga1;
    delete Tortuga2;
    delete Tortuga3;
    delete Tortuga4;
    delete Tortuga5;
    delete Tortuga6;
    delete Tortuga7;
    delete Halcon1;
    delete Halcon2;
    delete Halcon3;
    for (int i = nueces.size() - 1; 0 <= i; i--) removeItem(nueces.at(i));
    nueces.clear();
    m_platform=0;
    m_jumpAnimation->stop();
    scroll->setValue(0);
    Vida=Vida+1;

}

Mundos::~Mundos()
{
    delete per;
    delete ground;
    delete danger;
    delete background;
    delete Tortuga1;
    nueces.clear();
    ladrillosNota.clear();

}
