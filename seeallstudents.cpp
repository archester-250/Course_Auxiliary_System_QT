#include "seeallstudents.h"
#include "ui_seeallstudents.h"
#include "src/admin.h"

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

void SeeAllStudents::receiveName(QString name)
{
    this->name = name;
    Admin a(name.toStdString());
    for(int i = 0; i < a.getStudent_size(); i++)
    {
        QString text;
        text = QString::fromStdString("学生" + to_string(i + 1) + ":" + a.getStudents()[i].getName() + "\n");
        ui->textBrowser->insertPlainText(text);
        for(int j = 0; j < a.getStudents()[i].getCourseSize(); j++)
        {
            text = QString::fromStdString("\t修读课程：" + a.getStudents()[i].getCourses()[j].getName() + "\n");
            ui->textBrowser->insertPlainText(text);
            text = "\t作业完成情况：";
            for(int k = 0; k < a.getStudents()[i].getCourses()[j].getFinishSize(); k++)
            {
                text = QString::fromStdString("\t\t第" + to_string(k + 1) + "次作业：" + a.getStudents()[i].getCourses()[j].getHomeWork()[k]
                                              + "->");
                ui->textBrowser->insertPlainText(text);
                if(a.getStudents()[i].getCourses()[j].getFinish()[k].finish)
                {
                    text = "已完成\n";
                    ui->textBrowser->insertPlainText(text);
                }
                else
                {
                    text = "未完成\n";
                    ui->textBrowser->insertPlainText(text);
                }
            }
        }
    }
    qDebug() << "[LOG] administer " << name << " sees all students" << QString::fromStdString(modtime.toString());
}
