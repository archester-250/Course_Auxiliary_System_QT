#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateTime();
    ui->label_2->setText(QString::fromStdString("当前时间：" + modtime.toString()));
    m_nTimerID = this->startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_4_clicked()
{
    qDebug() << "[LOG] student login";
    StudentLogin sl;
    sl.exec();
}


void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << "[LOG] administer login";
    AdminLogin al;
    al.exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "[LOG] student register";
    StudentRegister sr;
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
    updateTime();
    ui->label_2->setText(QString::fromStdString("当前时间：" + modtime.toString()));
//    killTimer(m_nTimerID);
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << "[LOG] administer register";
    AdminRegister ar;
    ar.exec();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    rate = 10. / value;
    ui->label_4->setText(QString ::fromStdString("当前：" + to_string(value / 10.).substr(0, to_string(value / 10.).find('.') + 2)));
}

