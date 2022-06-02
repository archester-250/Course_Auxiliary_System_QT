#include "seehomework.h"
#include "ui_seehomework.h"

SeeHomework::SeeHomework(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeeHomework)
{
    ui->setupUi(this);
}

SeeHomework::~SeeHomework()
{
    delete ui;
}
