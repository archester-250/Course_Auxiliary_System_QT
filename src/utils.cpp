//
// Created by ll on 2022/4/15.
//
#include "utils.h"
#include "login.h"

int tmptime = clock();

void Time::pause() {
    tmptime = clock();
}

void Time::recover() {
    sys_time_bias_times += (clock() - tmptime);
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
                for (int i = 0; i < clockCheck->second.info->size; i++)
                    cout << "[事件提醒]" << clockCheck->second.info->get(i) << endl;
        }
    }
    sys_time_bias_times = SYS_TIME_BIAS_TIMES;
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
