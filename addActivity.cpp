﻿#include "addActivity.h"
#include "ui_addActivity.h"
#include "utils.h"
#include "hashMap.h"
#include "activity.h"
#include "student.h"
#include "course.h"
#include "login.h"
#include "input.h"

AddActivity::AddActivity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddActivity)
{
    ui->setupUi(this);
}

AddActivity::~AddActivity()
{
    delete ui;
}

void AddActivity::receiveName(QString name)
{
    this->name = name;
}

void AddActivity::on_pushButton_2_clicked()
{
    updateTime();
    Activity activity;
        Time startTime, endTime;
        int clk = 0;
        startTime.inputTime(ui->startTime->text().toInt());
        activity.setStartTime(startTime);
        endTime.inputTime(ui->endTime->text().toInt());
        activity.setEndTime(endTime);
        activity.setAddress(ui->address->text().toStdString());
        activity.setDescription(ui->description->text().toStdString());
        activity.setClk(ui->Clock->text().toInt());
        if (clk >= 0) {
            Time time = startTime.desc(clk);
            if (student->getClocks()->get(time.timeStamp())->first) {
                student->getClocks()->get(time.timeStamp())->second.addEvent(activity.toString());
            } else {
                Clock clock;
                clock.setTimestamp(time.timeStamp());
                clock.addEvent(activity.toString());
                student->getClocks()->put(time.timeStamp(), clock);
            }
        }
        clog << name.toStdString() << "添加事件：" << activity.toString() << endl;
        ofstream _config("../database/activities/" + name.toStdString(), ios::app);
        _config << activity.storeStr() << endl;
        _config.close();
        int memberCnt = ui->memberCnt->text().toInt();
        activity.setMemberCnt(0);//TODO
        for (int i = 0; i < activity.getMemberCnt(); i++) {
            _config.open("../database/activities/" + activity.getMembers()->get(i), ios::app);
            assert(_config);
            _config << activity.storeStr() << endl;
            _config.close();
        }
        student->getActivityArray()->push(activity);
        QMessageBox::information(NULL, "已添加", QString::fromStdString(activity.toString()));
}

