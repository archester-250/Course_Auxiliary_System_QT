#include "seeallcourses.h"
#include "ui_seeallcourses.h"

SeeAllCourses::SeeAllCourses(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeeAllCourses)
{
    ui->setupUi(this);
}

SeeAllCourses::~SeeAllCourses()
{
    delete ui;
}
