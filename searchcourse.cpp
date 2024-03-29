﻿#include "searchcourse.h"
#include "ui_searchcourse.h"

SearchCourse::SearchCourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchCourse)
{
    ui->setupUi(this);
    ui->textBrowser->hide();
}

SearchCourse::~SearchCourse()
{
    delete ui;
}

void SearchCourse::on_pushButton_2_clicked()
{
    QString courseName = ui->lineEdit->text();
    Student s(name.toStdString());
    vector<string> results;
    for(int z = 0; z < s.getCourseSize(); z++)
    {
        if(OurStr::SundaySearch(s.getCourses()[z].getName(), courseName.toStdString()) != -1)
        {
            results.push_back(s.getCourses()[z].getName());
        }
    }
    results = OurStr::Quick_Sort(results, 0, results.size() - 1);
    for(int z = 0; z < results.size(); z++)
    {
        course c;
        c = s.searchCourse(s.getCourses(), s.getCourseSize(), results[z]);
        ui->textBrowser->show();
        QString text;
        string weekday[7] = {"周一", "周二", "周三", "周四", "周五", "周六", "周日"};
        text += QString::fromStdString("课程名称：" + results[z] + "\n");
        text += "上课时间：\n";
        for(int i = 0; i < c.getTimeSize(); i++)
        {
            text += QString::fromStdString("\t" + to_string(i + 1) + "." + weekday[c.getTime()[i].week]
                    + " " + to_string(c.getTime()[i].starthour) + ".00-"
                    + to_string(c.getTime()[i].endhour) + ":00\n");
        }
        text += QString::fromStdString("上课地点：" + c.getAddress() + "\n");
        text += "课程资料：\n";
        for(int i = 0; i < c.getDocumentsSize(); i++)
        {
            text += QString::fromStdString("\t" + to_string(i + 1) + "." + c.getDocuments()[i] + "\n");
        }
        text += "课程作业：\n";
        for(int i = 0; i < c.getHomeWorkSize(); i++)
        {
            text += QString::fromStdString("\t" + to_string(i + 1) + "." + c.getHomeWork()[i] + "\n");
        }
        text += QString::fromStdString("课程QQ群：" + c.getQQGroup() + "\n");
        text += QString::fromStdString("考试时间：" + c.getExtime().toString() + "\n");
        text += QString::fromStdString("考试地点：" + c.getExaddress() + "\n\n");
        ui->textBrowser->insertPlainText(text);
    }
    if(results.size() == 0) QMessageBox::information(NULL, "无结果", "无对应课程！");
    qDebug() << "[LOG] student " << name << " tries to search keyword " << courseName << QString::fromStdString(modtime.toString());
}

void SearchCourse::receiveName(QString name)
{
    this->name = name;
}

