#include "adminmenu.h"
#include "ui_adminmenu.h"

AdminMenu::AdminMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminMenu)
{
    ui->setupUi(this);
}

AdminMenu::~AdminMenu()
{
    delete ui;
}

void AdminMenu::on_pushButton_clicked()
{
    SeeAllCourses sac;
    sac.setWindowTitle(QString::fromStdString("查看所有课程"));
    connect(this, SIGNAL(sendName(QString)), &sac, SLOT(receiveName(QString)));
    emit sendName(name);
    sac.exec();
}


void AdminMenu::on_pushButton_3_clicked()
{
    SeeAllStudents sas;
    sas.setWindowTitle(QString::fromStdString("查看所有学生"));
    connect(this, SIGNAL(sendName(QString)), &sas, SLOT(receiveName(QString)));
    emit sendName(name);
    sas.exec();
}


void AdminMenu::on_pushButton_5_clicked()
{
    AddCourse ac;
    ac.setWindowTitle(QString::fromStdString("添加课程"));
    connect(this, SIGNAL(sendName(QString)), &ac, SLOT(receiveName(QString)));
    emit sendName(name);
    ac.exec();
}


void AdminMenu::on_pushButton_2_clicked()
{
    AddHomework ah;
    ah.setWindowTitle(QString::fromStdString("添加作业"));
    connect(this, SIGNAL(sendName(QString)), &ah, SLOT(receiveName(QString)));
    emit sendName(name);
    ah.exec();
}

void AdminMenu::on_pushButton_6_clicked()
{
    AddCourseDoc acd;
    acd.setWindowTitle(QString::fromStdString("添加课程资料"));
    connect(this, SIGNAL(sendName(QString)), &acd, SLOT(receiveName(QString)));
    emit sendName(name);
    acd.exec();
}

void AdminMenu::receiveName(QString name)
{
    this->name = name;
}

