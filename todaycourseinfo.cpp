#include "todaycourseinfo.h"
#include "src/input.h"
#include "src/student.h"
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

void TodayCourseInfo::receiveName(QString name)
{
    this->name = name;
    string week[7] = {"周日", "周一", "周二", "周三", "周四", "周五", "周六"};
    QString text = QString::fromStdString("今天是" + modtime.toString() + "," + week[modtime.calculateWeekDay()] + "\n");
    ui->textBrowser->insertPlainText(text);
    Student s(name.toStdString());
    for (int i = 0; i < s.getCourseSize(); i++) {
        for (int j = 0; j < s.getCourses()[i].getTimeSize(); j++) {
            if (s.getCourses()[i].getTime()[j].week == modtime.calculateWeekDay()) {
                text = QString::fromStdString(s.getCourses()[i].getName() + "\t" +
                                              to_string(s.getCourses()[i].getTime()[j].starthour) + "时--" +
                                              to_string(s.getCourses()[i].getTime()[j].endhour) + "时\n");
                ui->textBrowser->insertPlainText(text);
            }
        }
    }
    qDebug() << "[LOG] student " << name << " sees today's courses";
}
