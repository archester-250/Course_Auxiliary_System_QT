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
    ic.exec();
}


void SystemChoose::on_pushButton_2_clicked()
{
    OutOfClass ooc;
    ooc.exec();
}

