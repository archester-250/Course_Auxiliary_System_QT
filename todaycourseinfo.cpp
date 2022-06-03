#include "todaycourseinfo.h"
#include "ui_todaycourseinfo.h"

TodayCourseInfo::TodayCourseInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TodayCourseInfo)
{
    ui->setupUi(this);
    ui->textBrowser->insertPlainText("jj");
    ui->textBrowser->insertPlainText("ii");
}

TodayCourseInfo::~TodayCourseInfo()
{
    delete ui;
}

void TodayCourseInfo::receiveName(QString name)
{
    this->name = name;
}
