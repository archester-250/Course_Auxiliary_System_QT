#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimerEvent>
#include "studentlogin.h"
#include "adminlogin.h"
#include "studentregister.h"
#include "adminregister.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void  handleTimeout();  //超时处理函数
    virtual void timerEvent( QTimerEvent *event);

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    int m_nTimerID;
    bool pause = false;
};
#endif // MAINWINDOW_H
