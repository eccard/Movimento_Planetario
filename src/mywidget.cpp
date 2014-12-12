#include "mywidget.h"
#include <QPicture>
#include <QTransform>
#include <math.h>
#include <iostream>
#include <fstream>

//double GM = 4*(M_PI*M_PI);//Massa Sol
//double MJMS = 0.0095; // Massa de Jupiter
//double MTMS = 3.e-6; // Massa da x


MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
    this->sol=QPixmap("sol2.png");
    this->terra=QPixmap("terra.png");
    this->jupiter=QPixmap("jupiter-.png");

    this->sol = this->sol.scaled(QSize(50,50));
    this->terra = this->terra.scaled((QSize(25,25)));
    this->jupiter = this->jupiter.scaled(QSize(75,75));

    timer = new QTimer(this);
    setTime(5);
    cont=0;

    this->t = 0.;
    this->dt=0.001;

    //terra
    this->y[0]= 1;       //x
    this->y[1]= 0;      // vx
    this->y[2]= 0;      //y
    this->y[3]= 2*M_PI;// vy
    //    this->y[3]= 2;// vy

    //Júpiter0.0095
    this->y[4]= 5.2;       //x
    this->y[5]= 0;      // vx
    this->y[6]= 0;      //y
    this->y[7]= 2.755;// vy



    //    background = QBrush(QColor(64, 32, 64));
    background = QBrush(Qt::black, Qt::SolidPattern);
    //    mainWindow = new MainWindow(parent);
    //    mainWindow->setvalueui(GM,MTMS,MJMS,2);
    setMassValues(4*(M_PI*M_PI),3.e-6,0.0095);
}
void MyWidget::deriv(double *y,double * dydt,double t ) {

    // distancias
    double r_t = sqrt(y[0]*y[0]+y[2]*y[2]) ;
    double r_j = sqrt (y[4]*y[4]+y[6]*y[6]) ;
    double r_tj = sqrt (pow(y[0]-y[4],2)+pow(y[2]-y[6],2)) ;
    double r_t3 = pow (r_t,3) ;
    double r_j3 = pow (r_j,3) ;
    double r_tj3 = pow (r_tj,3) ;
    // Terra
    dydt[0] = y[1];
    dydt[1] = -GM*y[0]/r_t3 - GM*MJMS*(y[0]-y[4])/r_tj3 ;
    dydt[2] = y[3];
    dydt[3] = -GM*y[2]/r_t3 - GM*MJMS*(y[2]-y[6])/r_tj3 ;
    // Jupiter
    dydt[4] = y[5];
    dydt[5] = -GM*y[4]/r_j3 - GM*MTMS*(y[4]-y[0])/r_tj3 ;
    dydt[6] = y[7];
    dydt[7] = -GM * y[6]/r_j3 - GM*MTMS*(y[6]-y[2])/r_tj3 ;
}
void MyWidget::runge_kutta(double *y,double t,double dt){
    int i ;
    double k1[8],k2[8],dydt[8],ypar[8];
    deriv (y,dydt,t);
    for (i =0;i<8;i++){
        k1[i]=dydt[i]* dt ;
        ypar[i]=y[i]+k1[i]/2.;
    }
    deriv(ypar,k2,t+dt/2.) ;
    for (i =0;i<8;i++) {
        y[i]+=k2[i]* dt ;
    }
}



void MyWidget::paintEvent(QPaintEvent *event)
{

    //create a QPainter and pass a pointer to the device.
    //A paint device can be a QWidget, a QPixmap or a QImage
    QPainter painter(this);
    glViewport(0,0,640,480);

    painter.fillRect(event->rect(),this->background);
    painter.drawPixmap(QPoint(550,300),this->sol);
    painter.drawPixmap(QPoint((this->xterra*100)+550,(this->yterra*100)+300),this->terra);
    painter.drawPixmap(QPoint((this->xjupiter*50)+550,(this->yjupiter*50)+300),this->jupiter);

    this->xterra=this->y[0];
    this->yterra=this->y[2];

    this->xjupiter=this->y[4];
    this->yjupiter=this->y[6];
    runge_kutta(this->y,this->t,this->dt);
    this->t+=this->dt;
}

void MyWidget::setMassValues(double GM, double MTMS, double MJMS){
    this->GM=GM;
    this->MTMS=MTMS;
    this->MJMS=MJMS;
//    emit change(GM,MJMS,MTMS);
//    qDebug() << "signal envied" << endl;
}

double MyWidget::getMassSol(){
    return this->GM;
}

double MyWidget::getMassTerra(){
    return this->MTMS;
}

double MyWidget::getMassJupiter(){
    return this->MJMS;
}
float MyWidget::getTime(){
    return this->time;
}

void MyWidget::setTime(float time){
//    disconnect(this->timer,SIGNAL(timeout()),this,SLOT(repaint()));
    this->time=time;
    timer->start(time);
    connect(this->timer,SIGNAL(timeout()),this,SLOT(repaint()));
//    qDebug() << "time =" << time<< endl;
}

void MyWidget::setMassSol(double msol){
    this->GM=msol;
}

void MyWidget::setMassTerra(double mterra){
    this->MTMS=mterra;
}

void MyWidget::setMassJupiter(double mjupiter){
    this->MJMS=mjupiter;
}
