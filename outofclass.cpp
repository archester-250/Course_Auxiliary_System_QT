#include "outofclass.h"
#include "login.h"
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
    connect(this, SIGNAL(sendName(QString)), &aa, SLOT(receiveName(QString)));
    aa.exec();
}


void OutOfClass::on_pushButton_2_clicked()
{
    SeeTodayActivities sta;
    connect(this, SIGNAL(sendName(QString)), &sta, SLOT(receiveName(QString)));
    sta.exec();
}


void OutOfClass::on_pushButton_3_clicked()
{
    SeeAllActivities saa;
    connect(this, SIGNAL(sendName(QString)), &saa, SLOT(receiveName(QString)));
    saa.exec();
}


void OutOfClass::on_pushButton_4_clicked()
{
    AddClock ac;
    connect(this, SIGNAL(sendName(QString)), &ac, SLOT(receiveName(QString)));
    ac.exec();
}


void OutOfClass::receiveName(QString name)
{
    this->name = name;
}
