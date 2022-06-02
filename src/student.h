/**
 * @file student.h
 * @author your name (you@domain.com)
 * @brief 完成学生类，在学生类下定义学生的一系列操作
 * @version 0.1
 * @date 2022-03-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef STUDENT_H
#define STUDENT_H

#include "utils.h"
#include "activity.h"
#include "course.h"
#include "hashMap.h"
#include <string>

class Activity;
class course;

bool time_conflict(int timestamp);

class Student {

private:
    string name;
    course * courses;
    HashMap<int, Activity>* activities = new HashMap<int, Activity>(32);
    HashMap<int, Clock>* clocks = new HashMap<int, Clock>(32);
    int course_size;
    Array<Activity>* Activities = new Array<Activity>(32);

public:
    Student();
    Student(string name);

    HashMap<int, Activity> *getActivities() const;

    ~Student()
    {
        for(int i = 0; i < course_size; i++)
        {
            courses[i].~course();
        }
        delete[] courses;
        delete Activities;
    }

    string getName();

    void setName(string name);

    int getCourseSize();

    void setCourseSize(int course_size);

    Array<Activity>* getActivityArray();

    course * getCourses();

    HashMap<int, Clock> *getClocks() const;

    void setCourses(course * courses, int c_count);

    void addActivity();

    void addClocks();

    course searchCourse(course c[], int size, string name);//搜索课程功能

    void showMenu();//显示学生操作菜单

    void showTodayCourse();//显示今天的课程

    void showActivities(bool today);

    void courseTable();

    void saveStuInfo();//保存数据至文件

    int showCourseMenu();//显示课程操作菜单

    int showActivityMenu();//显示活动操作菜单

    void InitStudent();//初始化学生信息

    void showCourseDetail();//显示课程详情

    void showCourseHw();//显示课程作业

    void uploadHw();//上传作业

    void showDoc();//显示资料
};

#endif