/**
 * @file activity.h
 * @author your name (you@domain.com)
 * @brief ��ɿ��������ܣ������趨���ӡ���ɾ��������Ϣ������Ƿ���ʱ���ص���
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
    Time endTime;//���ֹʱ��
    string address;
    int clk;
    int memberCnt;
    Array<string>* members;
    string description;//���������

public:
    virtual ~Activity();
    Activity();

    // Get �� Set ����
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