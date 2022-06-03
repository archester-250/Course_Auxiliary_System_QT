#include "addhomework.h"
#include "ui_addhomework.h"

AddHomework::AddHomework(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddHomework)
{
    ui->setupUi(this);
}

AddHomework::~AddHomework()
{
    delete ui;
}
