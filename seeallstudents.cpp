#include "seeallstudents.h"
#include "ui_seeallstudents.h"

SeeAllStudents::SeeAllStudents(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeeAllStudents)
{
    ui->setupUi(this);
}

SeeAllStudents::~SeeAllStudents()
{
    delete ui;
}
