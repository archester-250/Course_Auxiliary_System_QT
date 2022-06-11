#include "systemchoose.h"
#include "ui_systemchoose.h"

SystemChoose::SystemChoose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemChoose)
{
    ui->setupUi(this);
}

SystemChoose::~SystemChoose()
{
    delete ui;
}

void SystemChoose::on_pushButton_3_clicked()
{
    Inclass ic;
    ic.setWindowTitle(QString::fromStdString("课程管理系统"));
    connect(this, SIGNAL(sendName(QString)), &ic, SLOT(receiveName(QString)));
    emit sendName(name);
    ic.exec();
}


void SystemChoose::on_pushButton_2_clicked()
{
    OutOfClass ooc;
    ooc.setWindowTitle(QString::fromStdString("课外管理系统"));
    connect(this, SIGNAL(sendName(QString)), &ooc, SLOT(receiveName(QString)));
    emit sendName(name);
    ooc.exec();
}

void SystemChoose::receiveName(QString s)
{
    name = s;
}


void SystemChoose::on_pushButton_clicked()
{
    system("start NAV.EXE");
}

