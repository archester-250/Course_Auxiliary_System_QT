#include "addActivity.h"
#include "ui_addActivity.h"
#include "src/utils.h"
#include "src/hashMap.h"
#include "src/activity.h"
#include "src/student.h"
#include "src/login.h"
#include "src/input.h"

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
        if (time_conflict(startTime.timeStamp())){
                return;
        }
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
        ofstream _config("../database/activities/" + student->getName(), ios::app);
        _config << activity.storeStr() << endl;
        _config.close();
        storeStr = activity.storeStr();
        student->getActivityArray()->push(activity);
        QMessageBox::information(NULL, "已添加", QString::fromStdString(activity.toString()));
}

void AddActivity::on_pushButton_add_clicked(){
    if (storeStr == "NULL"){
        QMessageBox::information(NULL, "未定义行为", "需要先为自己增加此事件");
        return;
    }
    ofstream _config("../database/activities/" + ui->member->text().toStdString(), ios::app);
    _config << storeStr << endl;
    _config.close();
    QMessageBox::information(NULL, "已添加", QString::fromStdString(ui->member->text().toStdString() + " <- " + storeStr));
}

