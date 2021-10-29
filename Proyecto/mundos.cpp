/*

Clase mundos: clase que permite crear y eliminar la creacion de cada uno de los escenarios, valida el movimiento
del personaje, actualiza el estado del juego...

*/

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

            if (mundo1){


            if ((pant[0]->colision() || pant[1]->colision()||pant[2]->colision()||pant[3]->colision()) && per->fric == false){
                per->fric = true;
                per->new_spike(per->x(),150,8,1);
                per->activar_time();

            }else if ((pant[0]->colision() || pant[1]->colision()||pant[2]->colision()||pant[3]->colision()) == false){
                per->fric = false;
                per->desactivar_time();

            }else if (per->fric) per->new_spike(per->x(),150,8,1);


           }break;
        }


        case Qt::Key_Left:
        {
            reinicio=false;
            per->addDirection(-1);
            per->addStandingDirection(-1);
            checkTimer();

            if (mundo1){


            if ((pant[0]->colision() || pant[1]->colision()||pant[2]->colision()||pant[3]->colision()) && per->fric == false){
                per->fric = true;
                per->new_spike(per->x(),150,8,-1);
                per->activar_time();

            }else if ((pant[0]->colision() || pant[1]->colision()||pant[2]->colision()||pant[3]->colision()) == false){
                per->fric = false;
                per->desactivar_time();
            }else if (per->fric) per->new_spike(per->x(),150,8,-1);



        }break;
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
        puntos += Puntaje->getPuntaje();
    }

    int dx;
    if(per->isFalling()){
        return;
    }

    per->nextFrame();


    direction = per->direction();

    if (0 == direction) return;

    // REVISAR
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
        if (per->fric == false)per->moveBy(dx, 0);  // Aqui se mueve a la derecha
        int diff = per->pos().x() - scroll->value();

        if(diff > 850 && per-> x()<= 3800 - 820 + per->wid()){

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
        if (per->fric == false)per->moveBy(dx, 0); // Aqui se mueve a la izquierda
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
    mundo1 =true;
    setSceneRect(0,0,4800,720);
    nivelTierra = 660;



    //Ponemos posicion incial del cielo
    background=new Fondo(QPixmap(":/imagenes/fondo.png"));
    background->setPos(0,0);
    addItem(background);


    //add ground
    ground = new Fondo(QPixmap(":/imagenes/suelo.png"));
    ground->setPos(0,nivelTierra);
    addItem(ground);

    //puntaje
    LogoPuntaje = new Fondo(QPixmap(":/imagenes/puntaje.png"));
    LogoPuntaje->setPos(50, nivelTierra -627 );
    addItem(LogoPuntaje);
    Puntaje = new puntaje(puntos);
    Puntaje->setPos(150, nivelTierra - 647);
    addItem(Puntaje);

    //vidas
    LogoVida = new Fondo(QPixmap(":/imagenes/vidastxt.png"));
    LogoVida->setPos(50, nivelTierra - 550 );
    addItem(LogoVida);
    vidas_ = new vidas(Vida);
    Vida--;
    vidas_->setPos(150, nivelTierra - vidas_->boundingRect().height()-510);
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
    int posLadrillo[16][3] = {{400,500,3}, {650,300,3}, {950,400,3},{1240,200,2}, {1366,450,2},
                              {1600,520,8}, {1790,330,3}, {2100,200,3}, {2200,460,6}, {2800,460,3},
                              {3100,460,3}, {3460,400,3}, {3800,615,2}, {3800,575,2},{3800,535,2}};
    for (int i = ladrillosNota.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillosNota.at(i));
    }
    ladrillosNota.clear();
    for (int i = 0; i < 16; i++)
    {
        ladrillosNota.append(new MurosNota(posLadrillo[i][2]));
        ladrillosNota.last()->setPos(posLadrillo[i][0],posLadrillo[i][1]);
        addItem(ladrillosNota.last());
    }


  //  Agregamos nueces
    int posNueces[42][2] ={{800,600},{850,600},{900,600},{950,600},{1000,600},{1050,600},{1100,600},{1150,600},{1200,600}, {950,340},
                             {1100,340},{1000,340},{1050,340},{1610,460},{1660,460},{1710,460},{1760,460},{1810,460},{1860,460},{1910,460},{1960,460},{2010,460}
                              ,{2060,460},{2100,140},{2150,140},{2200,140},{2250,140},{2350,400},{2400,400},{2450,400},
                           {3150,400},{3100,400},{3200,400},{3250,400},{2800,400},{2900,400},{2850,400},{2950,400},{3300,600},{3350,600},
                           {3400,600},{3450,600}};//completas las 42
    for (int i = nueces.size() - 1; 0 <= i; i--)
    {
        removeItem(nueces.at(i));
    }
    nueces.clear();

    for (int i= 0; i <= 40;i++)
    {
        nueces.append(new Nueces());
        nueces.last()->setPos(posNueces[i][0], posNueces[i][1]);
        addItem(nueces.last());

    }



      for (int i = 0; i < 4; i++){
          pant[i] =new pantano;
          addItem (pant[i]);
          pant[i]->setPos(400+((i+1)*650),640);


      }

     //Agregamos los tortugas enemigas
      tortuga[0] = new Tortuga(800,1200);
      tortuga[0]->setPos(1200, nivelTierra-100);
      tortuga[1] = new Tortuga(1600,1900);
      tortuga[1]->setPos(1900, nivelTierra-230);
      tortuga[2] = new Tortuga(2100,2400);
      tortuga[2]->setPos(2400, nivelTierra-100);
      tortuga[3] = new Tortuga(3250,3500);
      tortuga[3]->setPos(3500, nivelTierra-100);
      tortuga[4] = new Tortuga(2400,2800);
      tortuga[4]->setPos(2800, nivelTierra-100);
      tortuga[5] = new Tortuga(2200,2400);
      tortuga[5]->setPos(2400, nivelTierra-280);
      tortuga[6]= new Tortuga(400,800);
      tortuga[6]->setPos(800, nivelTierra-100);



      for (int i = 0; i < 6; i++){
          addItem (tortuga[i]);
          connect(this->tortuga[i], SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      }

        //pasar a nivel 2
        next=new Next();
        next->setPos(3800,535-next->heigth());
        //3800,535,2
        addItem(next);
        connect(this->next, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

}

void Mundos::iniciarEscenaDos()
{
    mundo=true;
    mundo1=false;
    setSceneRect(0,0,4800,720);
    nivelTierra = 660;

    //Ponemos posicion incial del cielo
    background=new Fondo(QPixmap(":/imagenes/fondo_escena2.png"));
    background->setPos(0,0);
    addItem(background);


    //add ground
    ground = new Fondo(QPixmap(":/imagenes/suelo.png"));
    ground->setPos(0,nivelTierra);
    addItem(ground);

    //puntaje
    LogoPuntaje = new Fondo(QPixmap(":/imagenes/puntaje.png"));
    LogoPuntaje->setPos(50, nivelTierra -627 );
    addItem(LogoPuntaje);
    Puntaje = new puntaje(puntos);
    Puntaje->setPos(150, nivelTierra - 647);
    addItem(Puntaje);

    //vidas
    LogoVida = new Fondo(QPixmap(":/imagenes/vidastxt.png"));
    LogoVida->setPos(50, nivelTierra - 550 );
    addItem(LogoVida);
    vidas_ = new vidas(Vida);
    Vida--;
    vidas_->setPos(150, nivelTierra - vidas_->boundingRect().height()-510);
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
    int posLadrillo[16][3] = {{550,500,1}, {650,400,6}, {1366,450,2}, {1600,520,2},{1700,520,2}, {1740,300,3}
                             , {2300,460,2}, {2800,460,4}, {3800,615,2}, {3800,575,2},{3800,535,2}};

    for (int i = ladrillosNota.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillosNota.at(i));
    }
    ladrillosNota.clear();

    for (int i = 0; i < 16; i++)
    {
        ladrillosNota.append(new MurosNota(posLadrillo[i][2]));
        ladrillosNota.last()->setPos(posLadrillo[i][0],posLadrillo[i][1]);
        addItem(ladrillosNota.last());
    }


    //  Agregamos nueces
      int posNueces[42][2] ={{550,600},{1600,600},{650,600},{1700,600},{750,600},{3700,600},{850,600},{1900,600},{950,600},{1000,600},{1050,600},{2100,600},{1150,600},{3200,600}, {700,340},
                               {750,340},{800,340},{850,340},{900,340},{950,340},{1370,390},{1420,390},{1610,460},{1660,460},{1710,460},{1760,460},
                                {1740,235},{1790,235},{1840,235},{2295,400},{2345,400},{2395,400},{2750,600},{2800,400},{2850,400},{2900,400},{2950,400},{3000,400}
                               ,{2110,600},{1890,235},{2950,600},{3600,600}};
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


      //agregar enemigos escena2
         aranas[0] = new Aranas(20,500);
         aranas[0]->setPos(300, nivelTierra-500);
         aranas[1] = new Aranas(20,300);
         aranas[1]->setPos(600, nivelTierra-500);
         aranas[2] = new Aranas(20,400);
         aranas[2]->setPos(900, nivelTierra-500);
         aranas[3] = new Aranas(20,500);
         aranas[3]->setPos(1200, nivelTierra-500);
         aranas[4] = new Aranas(30,300);
         aranas[4]->setPos(1500, nivelTierra-500);
         aranas[5] = new Aranas(25,400);
         aranas[5]->setPos(1800, nivelTierra-500);
         aranas[6] = new Aranas(25,500);
         aranas[6]->setPos(2300, nivelTierra-500);
         aranas[7] = new Aranas(25,300);
         aranas[7]->setPos(2700, nivelTierra-500);


         aranita1 = new Fisica3(2700,300,2900,400,2);
         aranita1->setPos(2700,300);
         addItem(aranita1);
         connect(this->aranita1, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

         aranita2 = new Fisica3(2250,300,2450,400,-2);
         aranita2->setPos(2250,300);
         addItem(aranita2);
         connect(this->aranita2, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

        for (int i = 0; i < 7; i++){
             addItem (aranas[i]);
             connect(this->aranas[i], SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      }

      //Agregamos objeto para pasar al nivel 3
      next2 = new Next2();
      next2->setPos(3800,390);
      addItem(next2);
      connect(this->next2, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

      timer = new QTimer(this);
      connect(timer,SIGNAL(timeout()),this,SLOT(moverPersonaje()));
      timer->setInterval(20);
      mFallTimer = new QTimer(this);
      connect(mFallTimer,SIGNAL(timeout()),this,SLOT(fallPersonaje()));
      mFallTimer->setInterval(20);

      per->set_m_direction(0);
      per->addDirection(1);

}

void Mundos::iniciarEscenaTres()
{
    mundo = true;
    mundo1=false;
    setSceneRect(0,0,4800,720);
    nivelTierra = 660;


    background=new Fondo(QPixmap(":/imagenes/fondo_escena3.jpg"));
    background->setPos(0,0);
    addItem(background);


    ground = new Fondo(QPixmap(":/imagenes/suelo.png"));
    ground->setPos(0,nivelTierra);
    addItem(ground);

    //puntaje
    LogoPuntaje = new Fondo(QPixmap(":/imagenes/puntaje.png"));
    LogoPuntaje->setPos(50, nivelTierra -627 );
    addItem(LogoPuntaje);
    Puntaje = new puntaje(puntos);
    Puntaje->setPos(150, nivelTierra - 647);
    addItem(Puntaje);

    //vidas
    LogoVida = new Fondo(QPixmap(":/imagenes/vidastxt.png"));
    LogoVida->setPos(50, nivelTierra - 550 );
    addItem(LogoVida);
    vidas_ = new vidas(Vida);
    Vida--;
    vidas_->setPos(150, nivelTierra - vidas_->boundingRect().height()-510);
    addItem(vidas_);

    per = new Personaje(Jugador);
    per->setPos(50, nivelTierra - per->boundingRect().height() );
    addItem(per);

    if(configurar_){
        Jugador=true;
    }
    else Jugador=!Jugador;

    startTimer( 100 );

    int posLadrillo[16][3] = {{550,500,1}, {650,400,6}, {1366,450,2}, {1600,520,2},{1700,520,2}, {1740,300,3}
                             , {2300,460,2}, {2800,460,4}, {3800,615,3}, {3800,575,3},{3800,535,3},{3800,495,3}};
    for (int i = ladrillosNota.size() - 1; 0 <= i; i--)
    {removeItem(ladrillosNota.at(i));}

    ladrillosNota.clear();

    for (int i = 0; i < 16; i++)
    {   ladrillosNota.append(new MurosNota(posLadrillo[i][2]));
        ladrillosNota.last()->setPos(posLadrillo[i][0],posLadrillo[i][1]);
        addItem(ladrillosNota.last());}

      int posNueces[42][2] ={{550,600},{1600,600},{650,600},{1700,600},{750,600},{3700,600},{850,600},{1900,600},{950,600},{1000,600},{1050,600},{2100,600},{1150,600},{3200,600}, {700,340},
                               {750,340},{800,340},{850,340},{900,340},{950,340},{1370,390},{1420,390},{1610,460},{1660,460},{1710,460},{1760,460},
                                {1740,235},{1790,235},{1840,235},{2295,400},{2345,400},{2395,400},{2750,600},{2800,400},{2850,400},{2900,400},{2950,400},{3000,400}
                               ,{2110,600},{1890,235},{2950,600},{3600,600}};
      for (int i = nueces.size() - 1; 0 <= i; i--)
      { removeItem(nueces.at(i));}

      nueces.clear();

      for (int i= 0; i < 40;i++){
          nueces.append(new Nueces());
          nueces.last()->setPos(posNueces[i][0], posNueces[i][1]);
          addItem(nueces.last());}

      //Agregamos Halcones
        halcon[0]=new Halcon(300,700);
        halcon[0]->setPos(650,50);
        halcon[1]=new Halcon(700,1100);
        halcon[1]->setPos(1050,50);
        halcon[2]=new Halcon(1100,1500);
        halcon[2]->setPos(1450,50);
        halcon[3]=new Halcon(1500,1900);
        halcon[3]->setPos(1850,50);
        halcon[4]=new Halcon(1900,2300);
        halcon[4]->setPos(2250,50);
        halcon[5]=new Halcon(2300,2700);
        halcon[5]->setPos(2650,50);
        halcon[6]=new Halcon(2700,3100);
        halcon[6]->setPos(3050,50);
        halcon[7]=new Halcon(3100,3400);
        halcon[7]->setPos(3350,50);
        halcon[8]=new Halcon(3400,3800);
        halcon[8]->setPos(3750,50);


        for (int i=0;i<9;i++){
            addItem(halcon[i]);
            connect(this->halcon[i], SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));
        }

        //item para finalizar juego
        final=new casa();
        final->setPos(3780,510-final->heigth());
        addItem(final);
        connect(this->final, SIGNAL(estadoJuego(int)),this, SLOT(Estado(int)));

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

//------------- COLICIONES --
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
            puntos++;
            Puntaje->incrementar(puntos);
            nueces=eliminarnueces(nueces,i);

         }
    }
}


//se elimina las nueces una vez colisionada
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
        reiniciarEscenaTres();
        ganar = new Triunfo();
        ganar->setWindowFlags(((ganar->windowFlags()|Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
        ganar->exec();
    }
    else if(number == 5){
       Borrarmundo2();
       iniciarEscenaTres();
    }
    else if(number == 6){
        if (Vida==0){
            reiniciarEscenaTres();
            gameOverWindow = new GameOver();
            gameOverWindow->setWindowFlags(((gameOverWindow->windowFlags()|Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
            gameOverWindow->exec();
        }
        else reiniciarEscenaTres();
    }
    else return;
}

//se eliminan los objetos del primer mundo
void Mundos::reiniciarEscenaUno()
{
    delete per;
    delete next;
    delete timer;
    delete mFallTimer;
    delete background;
    delete ground;
    delete Puntaje;
    delete LogoPuntaje;
    delete LogoVida;

    for(int i=0;i<4;i++){
       removeItem(pant[i]);
       delete pant[i];
    }

    for(int i=0;i<6;i++){
       removeItem(tortuga[i]);
       delete tortuga[i];       
    }


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

//se eliminan los objetos del segundo mundo
void Mundos::reiniciarEscenaDos()
{
    delete per;
    delete timer;
    delete next2;
    delete mFallTimer;
    delete background;
    delete ground;
    delete Puntaje;
    delete LogoPuntaje;
    delete LogoVida;

    for(int i=0;i<7;i++){
       removeItem(aranas[i]);
       delete aranas[i];}

    delete aranita1;
    delete aranita2;

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
//se eliminan los objetos del Tercer mundo
void Mundos::reiniciarEscenaTres()
{
    delete per;
    delete timer;
    delete final;//casa
    delete mFallTimer;
    delete background;
    delete ground;
    delete Puntaje;
    delete LogoPuntaje;
    delete LogoVida;
    for(int i=0;i<8;i++){
       removeItem(halcon[i]);
       delete halcon[i];
    }

    m_platform=0;
    m_jumpAnimation->stop();
    scroll->setValue(0);
    iniciarEscenaTres();

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

// se eliminan los objetos del primer mundo
void Mundos::Borrarmundo1()
{
    delete per;
    delete timer;
    delete mFallTimer;
    delete background;
    delete ground;
    delete Puntaje;
    delete next;
    delete LogoPuntaje;
    delete LogoVida;

    for(int i=0;i<6;i++){
       removeItem(tortuga[i]);
       delete tortuga[i];}

    for(int i=0;i<4;i++){
       removeItem(pant[i]);
       delete pant[i];
    }


    for (int i = nueces.size() - 1; 0 <= i; i--) removeItem(nueces.at(i));
        nueces.clear();



     for (int i = ladrillosNota.size() - 1; 0 <= i; i--)
         {
         removeItem(ladrillosNota.at(i));
         delete ladrillosNota.at(i);}

     ladrillosNota.clear();


    m_platform=0;
    m_jumpAnimation->stop();
    scroll->setValue(0);
    Vida=Vida+1;

}

void Mundos::Borrarmundo2()
{
    delete per;
    delete timer;
    delete mFallTimer;
    delete background;
    delete ground;
    delete Puntaje;
    delete next2;
    delete LogoPuntaje;
    delete LogoVida;

    delete aranita1;
    delete aranita2;

    for(int i=0;i<7;i++){
      removeItem(aranas[i]);
      delete aranas[i];}

    for (int i = nueces.size() - 1; 0 <= i; i--) removeItem(nueces.at(i));

    nueces.clear();



   for (int i = ladrillosNota.size() - 1; 0 <= i; i--)
    {
        removeItem(ladrillosNota.at(i));
        delete ladrillosNota.at(i);}

    ladrillosNota.clear();

    m_platform=0;
    m_jumpAnimation->stop();
    scroll->setValue(0);
    Vida=Vida+1;

}

Mundos::~Mundos()
{
    delete per;
    delete timer;
    delete mFallTimer;
    delete background;
    delete ground;
    delete Puntaje;
    delete LogoPuntaje;
    delete LogoVida;

    nueces.clear();
    ladrillosNota.clear();

}
