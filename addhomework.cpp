#include "addhomework.h"
#include "ui_addhomework.h"
#include "src/admin.h"

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

void AddHomework::receiveName(QString name)
{
    this->name = name;
}

void AddHomework::on_pushButton_2_clicked()
{
    Admin a(name.toStdString());
    string courseName = ui->lineEdit->text().toStdString();
    string homework = ui->lineEdit_2->text().toStdString();
    if(courseName.empty() || homework.empty())
    {
        QMessageBox::information(NULL, "Error", "请将输入补充完整！");
        return;
    }
    Student s;
    course c = s.searchCourse(a.getCourses(), a.getCourse_size(), courseName);
    if(c.getName() == "null")
    {
        QMessageBox::information(NULL, "Error", "未找到该课程！");
        return;
    }
    bool flag = false;
    for(int j = 0; j < c.getHomeWorkSize(); j++)
    {
        if(!OurStr::StrCmp(homework, c.getHomeWork()[j]))
        {
            flag = true;
            break;
        }
    }
    if(flag)
    {
        QMessageBox::information(NULL, "Error", "该作业已存在！");
        return;
    }
    a.addHomework(courseName, homework);
    qDebug() << "[LOG] administer " << name << " adds homework " << QString::fromStdString(homework)
             << " to " << QString::fromStdString(courseName);
    a.saveAdminInfo();
}
