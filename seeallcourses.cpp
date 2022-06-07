#include "seeallcourses.h"
#include "ui_seeallcourses.h"
#include "src/admin.h"

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

void SeeAllCourses::receiveName(QString name)
{
    this->name = name;
    Admin a(name.toStdString());
    for(int i = 0; i < a.getCourse_size(); i++)
    {
        QString text;
        string weekday[7] = {"周一", "周二", "周三", "周四", "周五", "周六", "周日"};
        text += QString::fromStdString("课程名称：" + a.getCourses()[i].getName() + "\n");
        text += "上课时间：\n";
        for(int j = 0; j < a.getCourses()[i].getTimeSize(); j++)
        {
            text += QString::fromStdString("\t" + to_string(j + 1) + "." + weekday[a.getCourses()[i].getTime()[j].week]
                    + " " + to_string(a.getCourses()[i].getTime()[j].starthour) + ".00-"
                    + to_string(a.getCourses()[j].getTime()[j].endhour) + ":00\n");
        }
        text += QString::fromStdString("上课地点：" + a.getCourses()[i].getAddress() + "\n");
        text += "课程资料：\n";
        for(int j = 0; j < a.getCourses()[j].getDocumentsSize(); j++)
        {
            text += QString::fromStdString("\t" + to_string(j + 1) + "." + a.getCourses()[i].getDocuments()[j] + "\n");
        }
        text += "课程作业：\n";
        for(int j = 0; i < a.getCourses()[j].getHomeWorkSize(); j++)
        {
            text += QString::fromStdString("\t" + to_string(j + 1) + "." + a.getCourses()[i].getHomeWork()[j] + "\n");
        }
        text += QString::fromStdString("课程QQ群：" + a.getCourses()[i].getQQGroup() + "\n");
        text += QString::fromStdString("考试时间：" + a.getCourses()[i].getExtime().toString() + "\n");
        text += QString::fromStdString("考试地点：" + a.getCourses()[i].getExaddress() + "\n" + "\n");
        ui->textBrowser->insertPlainText(text);
    }
    qDebug() << "[LOG] administer " << name << " sees all courses";
}
