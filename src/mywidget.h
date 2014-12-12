#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QtGui>
#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <mainwindow.h>
class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);

    QTimer* timer;
    int cont;
    double y[8];
    double t;
    double getMassSol();
    double getMassTerra();
    double getMassJupiter();
    float getTime();


    void setMassSol(double msol);
    void setMassTerra(double mterra);
    void setMassJupiter(double mjupiter);
    void setTime(float time);
    void setMassValues(double GM,double MJMS, double MTMS);
protected:
    void paintEvent(QPaintEvent *event);
    QPixmap sol;
    QPixmap terra;
    QPixmap jupiter;
    double xterra;
    double yterra;
    double xjupiter;
    double yjupiter;
    double dt , x_teo,p0,r ;

    QBrush background;

private:
    double GM; //massa sol
    double MTMS; // massa terra
    double MJMS; // massa Jupiter
    float time;

    void deriv(double *y,double * dydt,double t );
    void runge_kutta(double *y,double t,double dt);
};

#endif // MYWIDGET_H
