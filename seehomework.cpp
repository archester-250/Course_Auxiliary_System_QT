#include "seehomework.h"
#include "ui_seehomework.h"
#include "src/student.h"

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

void SeeHomework::receiveName(QString name)
{
    this->name = name;
}

void SeeHomework::on_pushButton_2_clicked()
{
    string courseName = ui->lineEdit_2->text().toStdString();
    if(courseName.empty())
    {
        QMessageBox::information(NULL, "Error", "输入课程为空!");
        return;
    }
    Student s(name.toStdString());
    course c;
    c = s.searchCourse(s.getCourses(), s.getCourseSize(), courseName);
    if(c.getName() != "null")
    {
        QString text;
        for(int i = 0; i < c.getHomeWorkSize(); i++)
        {
            text = QString::fromStdString(to_string(i + 1) + "." + c.getHomeWork()[i] + "\n");
            ui->textBrowser->insertPlainText(text);
        }
    }
    else
    {
        QMessageBox::information(NULL, "Error", "未发现该课程!");
    }
}

