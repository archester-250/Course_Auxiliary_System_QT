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
    sac.exec();
}


void AdminMenu::on_pushButton_3_clicked()
{
    SeeAllStudents sas;
    sas.exec();
}


void AdminMenu::on_pushButton_5_clicked()
{
    AddCourse ac;
    ac.exec();
}


void AdminMenu::on_pushButton_2_clicked()
{
    AddHomework ah;
    ah.exec();
}


void AdminMenu::on_pushButton_4_clicked()
{
    SeeCourseDoc scd;
    scd.exec();
}


void AdminMenu::on_pushButton_6_clicked()
{
    AddCourseDoc acd;
    acd.exec();
}

