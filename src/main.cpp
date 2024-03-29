﻿/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 主程序
 * @version 0.1
 * @date 2022-03-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MAIN
#define MAIN

#define DEBUG
#include "login.h"
#include "student.h"
#include "admin.h"
#include <ctime>
#include <fstream>
#include <io.h>
#include "hashMap.h"


HashMap<int, Student> students(128);

using namespace std;

extern Student * student;
extern Admin * admin;
Time modtime;
int systime = clock();
float rate = 1.f;
int bias = 0;
int sys_time_bias_times = SYS_TIME_BIAS_TIMES * rate;

void updateTime()
{
    if (clock() - systime + bias > sys_time_bias_times){
        modtime.incre((clock() - systime + bias) / sys_time_bias_times);
        bias = (clock() - systime + bias) % sys_time_bias_times;
        systime = clock();
    }
}


streambuf *clogbuf = std::clog.rdbuf();

#endif

