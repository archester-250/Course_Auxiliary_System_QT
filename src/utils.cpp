﻿//
// Created by ll on 2022/4/15.
//
#include "utils.h"
#include "login.h"
#include <QMessageBox>


int tmptime = clock();
extern int systime;

void Time::pause() {
    tmptime = clock();
}

void Time::recover() {
    systime = clock();
}

string Time::toString() {
    return to_string(yr) + "年" + to_string(mn) + "月" + to_string(day) + "日" + to_string(hr) + "时 ";
}

void Time::incre(int h) {
    while (h--) {
        if (hr == 23) {
            hr = 0;
            if (day == MonthDays(yr, mn)) {
                day = 1;
                if (mn < 12)
                    mn++;
                else{
                    mn = 1;
                    yr++;
                }
            } else
                day++;
        } else
            hr++;
        if (student != nullptr) {
            auto clockCheck = student->getClocks()->get(modtime.timeStamp());
            if (clockCheck->first) {
                for (int i = 0; i < clockCheck->second.info->size; i++){
                    cout << "[clock]" << clockCheck->second.info->get(i) << endl;
                    QMessageBox::information(NULL, "闹钟", QString::fromStdString(clockCheck->second.info->get(i)));
                    }
        }
    }
    sys_time_bias_times = SYS_TIME_BIAS_TIMES * rate;
//    cout << "[当前时间]" << toString() << "星期" << calculateWeekDay() << endl;
    }
}

Clock::Clock() {}

int Clock::getTimestamp() const {
    return timestamp;
}

void Clock::setTimestamp(int timestamp) {
    Clock::timestamp = timestamp;
}

Array<string> *Clock::getInfo() const {
    return info;
}

void Clock::setInfo(Array<string> *info) {
    Clock::info = info;
}

Clock::Clock(int timestamp) : timestamp(timestamp) {}

bool Clock::addEvent(string event) {
    info->push(event);
    return true;
}
