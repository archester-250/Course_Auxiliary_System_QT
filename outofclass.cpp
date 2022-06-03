#include "outofclass.h"
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

void OutOfClass::receiveName(QString name)
{
    this->name = name;
}
