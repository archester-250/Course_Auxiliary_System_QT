#include "todaycourseinfo.h"
#include "ui_todaycourseinfo.h"

TodayCourseInfo::TodayCourseInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TodayCourseInfo)
{
    ui->setupUi(this);
}

TodayCourseInfo::~TodayCourseInfo()
{
    delete ui;
}
