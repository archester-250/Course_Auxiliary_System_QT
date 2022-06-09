#include "outofclass.h"
#include "src/login.h"
#include "ui_outofclass.h"

OutOfClass::OutOfClass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OutOfClass)
{
    ui->setupUi(this);
}

OutOfClass::~OutOfClass()
{
    delete ui;
}


void OutOfClass::on_pushButton_clicked()
{
    AddActivity aa;
    aa.setWindowTitle(QString::fromStdString("添加活动"));
    connect(this, SIGNAL(sendName(QString)), &aa, SLOT(receiveName(QString)));
    emit sendName(name);
    aa.exec();
}


void OutOfClass::on_pushButton_2_clicked()
{
    SeeTodayActivities sta;
    sta.setWindowTitle(QString::fromStdString("查看今日活动"));
    connect(this, SIGNAL(sendName(QString)), &sta, SLOT(receiveName(QString)));
    emit sendName(name);
    sta.exec();
}


void OutOfClass::on_pushButton_3_clicked()
{
    SeeAllActivities saa;
    saa.setWindowTitle(QString::fromStdString("查看所有活动"));
    connect(this, SIGNAL(sendName(QString)), &saa, SLOT(receiveName(QString)));
    emit sendName(name);
    saa.exec();
}


void OutOfClass::on_pushButton_4_clicked()
{
    AddClock ac;
    ac.setWindowTitle(QString::fromStdString("添加闹钟"));
    connect(this, SIGNAL(sendName(QString)), &ac, SLOT(receiveName(QString)));
    emit sendName(name);
    ac.exec();
}


void OutOfClass::receiveName(QString name)
{
    this->name = name;
}
