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
    connect(this, SIGNAL(sendName(QString)), &tci, SLOT(receiveName(QString)));
    emit sendName(name);
    tci.exec();
}


void Inclass::on_pushButton_3_clicked()
{
    Student s(name.toStdString());
    s.courseTable();
    QMessageBox::information(NULL, "message", "导出成功！");
}


void Inclass::on_pushButton_5_clicked()
{
    SearchCourse sc;
    connect(this, SIGNAL(sendName(QString)), &sc, SLOT(receiveName(QString)));
    emit sendName(name);
    sc.exec();
}


void Inclass::on_pushButton_2_clicked()
{
    SeeHomework sh;
    connect(this, SIGNAL(sendName(QString)), &sh, SLOT(receiveName(QString)));
    emit sendName(name);
    sh.exec();
}


void Inclass::on_pushButton_4_clicked()
{
    UploadHomework uh;
    connect(this, SIGNAL(sendName(QString)), &uh, SLOT(receiveName(QString)));
    emit sendName(name);
    uh.exec();
}


void Inclass::on_pushButton_6_clicked()
{
    OpenFile of;
    connect(this, SIGNAL(sendName(QString)), &of, SLOT(receiveName(QString)));
    emit sendName(name);
    of.exec();
}

void Inclass::receiveName(QString name)
{
    this->name = name;
}
