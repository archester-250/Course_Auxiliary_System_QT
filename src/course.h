/**
 * @file course.h
 * @author your name (you@domain.com)
 * @brief �γ̹����ܣ�������ɾ�����Ϣ���ϴ�����ѹ�����ϵȹ���
 * @version 0.1
 * @date 2022-03-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef COURSE_H
#define COURSE_H

#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include "utils.h"
#include "compression.h"
#include "input.h"
extern void updateTime();

struct course_time
{
    int week;//�ܼ�,��Χ0-6
    int starthour;//��ʼʱ��
    int endhour;//����ʱ��
};

struct hw_con
{
    bool finish;
    string road = "null";//������ҵ������
    string MD5 = "null";
};

using namespace std;


class course
{
private:
    /* data */
    string name;
    course_time * time;
    int t_size;
    string address;
    string * documents;//�γ�����
    int doc_size;
    string current;
    string * homeWork;//��ʾ����ҵ����
    int hw_size;
    string QQGroup;
    Time extime;
    string exaddress;//-exǰ׺�����������Ϣ
    hw_con * finish_con;
    int finish_size;
public:
    course();
    course(         string name,
                    course_time * time,
                    int t_size,
                    string address,
                    string * documents,
                    int doc_count,
                    string current,
                    string * homeWork,
                    int hw_size,
                    string QQGroup,
                    Time extime,
                    string exaddress);
    ~course(){
        if(t_size > 0)
        {
            delete [] time;
            time = NULL;
            t_size = 0;
        }
        if(doc_size > 0)
        {
            delete [] documents;
            documents = NULL;
            doc_size = 0;
        }
        if(hw_size > 0)
        {
            delete [] homeWork;
            homeWork = NULL;
            hw_size = 0;
        }
        if(finish_size > 0)
        {
            delete [] finish_con;
            finish_con = NULL;
            finish_size = 0;
        }
    }
    string getName();
    void setName(string name);
    course_time * getTime();
    void setTime(course_time * time, int size);
    int getTimeSize();
    void setTimeSize(int size);
    string getAddress();
    void setAddress(string address);
    string * getDocuments();
    void setDocuments(string * documents, int size);
    int getDocumentsSize();
    void setDocumentsSize(int size);
    string getCurrent();
    void setCurrent(string current);
    string * getHomeWork();
    void setHomeWork(string * homeWork, int size);
    int getHomeWorkSize();
    void setHomeWorkSize(int size);
    Time getExtime();
    void setExtime(Time extime);
    string getExaddress();
    void setExaddress(string exaddress);
    string getQQGroup();
    void setQQGroup(string QQGroup);
    hw_con * getFinish();
    void setFinish(hw_con * finish_con, int size);
    int getFinishSize();
    void setFinishSize(int size);
    course& operator=(const course& c);

    void uploadHomework(string road, string stuName, int no);
    void viewDocument(string course_name);
};


#endif