#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    changeValueUi(ui->widget->getMassSol(),ui->widget->getMassTerra(),ui->widget->getMassJupiter(),ui->widget->getTime());
    this->setWindowTitle("Movimento Planetário");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::changeValueUi(double massaSol, double massaTerra, double massaJupiter,float time){
    ui->spin_massa_sol->setValue(massaSol);
    ui->spin_massa_terra->setValue(massaTerra);
    ui->spin_massa_jupiter->setValue(massaJupiter);
    ui->spin_timer->setValue(time);
//    qDebug() << "signal recieved" << endl;
}
void MainWindow::changeValueFromUi(double massaSol,double massaTerra,double massaJupiter,float time){
    ui->widget->setMassValues(massaSol,massaTerra,massaJupiter);
    ui->widget->setTime(time);
}

void MainWindow::on_ok_clicked()
{
    disconnect(ui->widget->timer,SIGNAL(timeout()),ui->widget,SLOT(repaint()));
    changeValueFromUi(ui->spin_massa_sol->value(),ui->spin_massa_terra->value(),ui->spin_massa_jupiter->value(),ui->spin_timer->value());
}

void MainWindow::on_reset_clicked()
{
    disconnect(ui->widget->timer,SIGNAL(timeout()),ui->widget,SLOT(repaint()));
    ui->widget->setMassValues(4*(M_PI*M_PI),3.e-6,0.0095);
    ui->widget->setTime(5);
    changeValueUi(ui->widget->getMassSol(),ui->widget->getMassTerra(),ui->widget->getMassJupiter(),ui->widget->getTime());
}

void MainWindow::on_restart_clicked()
{
    ui->widget->t=0;

    ui->widget->y[0]= 1;       //x
    ui->widget->y[1]= 0;      // vx
    ui->widget->y[2]= 0;      //y
    ui->widget->y[3]= 2*M_PI;// vy

    //Júpiter0.0095
    ui->widget->y[4]= 5.2;       //x
    ui->widget->y[5]= 0;      // vx
    ui->widget->y[6]= 0;      //y
    ui->widget->y[7]= 2.755;// vy

}
