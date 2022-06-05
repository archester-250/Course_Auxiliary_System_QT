#include "addClock.h"
#include "ui_addClock.h"
#include "utils.h"
#include "hashMap.h"
#include "activity.h"
#include "student.h"
#include "course.h"
#include "login.h"
#include "input.h"

AddClock::AddClock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClock)
{
    ui->setupUi(this);
}

AddClock::~AddClock()
{
    delete ui;
}

void AddClock::receiveName(QString name)
{
    this->name = name;
}

void AddClock::on_pushButton_2_clicked()
{
    updateTime();
        int timestamp = modtime.timeStamp(), rep = 0, interval = 1;
        Time time;
        timestamp = ui->time->text().toInt();
        time.inputTime(timestamp);
        interval = ui->interval->text().toInt();
        rep = ui->cnt->text().toInt();
        string description = ui->content->text().toStdString();

        for (int i = 0; i < rep; i++) {
            Clock clock;
            clock.setTimestamp(time.timeStamp());
            clock.addEvent(description);
            student->getClocks()->put(time.timeStamp(), clock);
            clog << student->getName() << "已设置" << time.toString() << "的闹钟" << endl;
            time.incre(interval);
            ofstream _config("../database/clocks/" + student->getName(), ios::app);
            _config << clock.timestamp << " " << description << endl;
            _config.close();
        }
        QMessageBox::information(NULL, "已添加", QString::fromStdString(time.toString()));
        return;
}

