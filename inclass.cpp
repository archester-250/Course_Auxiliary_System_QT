#include "inclass.h"
#include "ui_inclass.h"

Inclass::Inclass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inclass)
{
    ui->setupUi(this);
}

Inclass::~Inclass()
{
    delete ui;
}

void Inclass::on_pushButton_clicked()
{
    TodayCourseInfo tci;
    tci.exec();
}


void Inclass::on_pushButton_3_clicked()
{
    QMessageBox::information(NULL, "message", "导出成功！");
}


void Inclass::on_pushButton_5_clicked()
{
    SearchCourse sc;
    sc.exec();
}


void Inclass::on_pushButton_2_clicked()
{
    SeeHomework sh;
    sh.exec();
}


void Inclass::on_pushButton_4_clicked()
{
    UploadHomework uh;
    uh.exec();
}


void Inclass::on_pushButton_6_clicked()
{
    OpenFile of;
    of.exec();
}

