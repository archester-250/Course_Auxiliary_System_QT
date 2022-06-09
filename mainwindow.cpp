#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "src/utils.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateTime();
    ui->label_2->setText(QString::fromStdString("当前时间：" + modtime.toString()));
    m_nTimerID = this->startTimer(1000);
    ui->pushButton_6->setStyleSheet("border-image: url(:/images/pause.png)");
    this->setStyleSheet("QMainWindow {border-image:url(:/images/yuanshen.png)}");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_4_clicked()
{
    qDebug() << "[LOG] student login" << QString::fromStdString(modtime.toString());
    StudentLogin sl;
    sl.setWindowTitle(QString::fromStdString("学生登录"));
    sl.exec();
}


void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << "[LOG] administer login" << QString::fromStdString(modtime.toString());
    AdminLogin al;
    al.setWindowTitle(QString::fromStdString("管理员登录"));
    al.exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "[LOG] student register" << QString::fromStdString(modtime.toString());
    StudentRegister sr;
    sr.setWindowTitle(QString::fromStdString("学生注册"));
    sr.exec();
}


void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_nTimerID){
        handleTimeout();
    }
}

void MainWindow::handleTimeout()
{
//    qDebug()<<"Enter timeout processing function\n";
    if(!pause)
    {
        updateTime();
        ui->label_2->setText(QString::fromStdString("当前时间：" + modtime.toString()));
    }
//    killTimer(m_nTimerID);
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << "[LOG] administer register" << QString::fromStdString(modtime.toString());
    AdminRegister ar;
    ar.setWindowTitle(QString::fromStdString("管理员注册"));
    ar.exec();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    rate = 10. / value;
    ui->label_4->setText(QString ::fromStdString("当前：" + to_string(value / 10.).substr(0, to_string(value / 10.).find('.') + 2)));
}


void MainWindow::on_pushButton_6_clicked()
{
    if(!pause)
    {
        ui->pushButton_6->setStyleSheet("border-image: url(:/images/play-one.png)");
        pause = true;
    }
    else
    {
        ui->pushButton_6->setStyleSheet("border-image: url(:/images/pause.png)");
        pause = false;
        systime = clock();
    }
}

