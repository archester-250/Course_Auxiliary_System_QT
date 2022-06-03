/**
 * @file activity.h
 * @author your name (you@domain.com)
 * @brief 完成课外活动管理功能，包括设定闹钟、增删查改相关信息、检测是否有时间重叠等
 * @version 0.1
 * @date 2022-03-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <iostream>
#include "utils.h"
#include <string>
#include <cstring>

class Time;

class Activity {
private:
    Time startTime;
    Time endTime;//活动起止时间
    string address;
    int clk;
    int memberCnt;
    Array<string>* members;
    string description;//活动内容描述

public:
    virtual ~Activity();
    Activity();

    // Get 和 Set 方法
    const Time &getStartTime() const;

    void setStartTime(Time startTime);

    const Time &getEndTime() const;

    void setEndTime(Time endTime);

    const string &getAddress() const;

    void setAddress(const string &address);


    int getClk() const;

    void setClk(int clk);

    int getMemberCnt() const;

    void setMemberCnt(int memberCnt);

    const string &getDescription() const;

    Array<string> *getMembers() const;

    void setMembers(Array<string> *members);

    void setDescription(const string &description);

    string toString();

    string storeStr();
};


#endif
