#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
public slots:
    void changeValueUi(double massaSol,double massaTerra,double massaJupiter,float time);
    void changeValueFromUi(double massaSol,double massaTerra,double massaJupiter,float time);
private slots:
    void on_ok_clicked();
    void on_reset_clicked();
    void on_restart_clicked();
};

#endif // MAINWINDOW_H
