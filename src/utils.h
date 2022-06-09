#ifndef COURSE_AUXILIARY_SYSTEM_UTILS_H
#define COURSE_AUXILIARY_SYSTEM_UTILS_H
#include "hashMap.h"
#include "MD5.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <io.h>

#define SYS_TIME_BIAS_TIMES 3000
//时间倍率，现在是3秒一小时

using namespace std;

extern int sys_time_bias_times;
extern int systime;

class Time {
public:
    int yr = 0, mn = 0, day = 0, hr = 0;
    int timestamp = timeStamp();

    int MonthDays(int yr, int mn) {
        switch (mn) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                return 31;
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;
            case 2:
                if (yr % 400 == 0) {
                    return 29;
                } else if (yr % 100 == 0) {
                    return 28;
                } else if (yr % 4 == 0) {
                    return 29;
                } else
                    return 28;

        }
        return 28;
    }

    Time desc(int h) {//????hС?
        while (h--) {
            if (hr == 0) {
                hr = 24;
                if (day == 1) {
                    if (mn != 1) {
                        day = MonthDays(yr, mn - 1);
                        mn--;
                    } else {
                        day = 31;
                        mn = 12;
                        yr--;
                    }
                } else
                    day--;
            }
            hr--;
        }
        return *this;
    }


    int inputTime(int _timestamp) {
        hr = _timestamp % 100;
        _timestamp /= 100;
        day = _timestamp % 100;
        _timestamp /= 100;
        mn = _timestamp % 100;
        _timestamp /= 100;
        yr = _timestamp + 2000;
        return EXIT_SUCCESS;
    }

    int timeStamp() const {
        return hr + day * 100 + mn * 10000 + (yr % 100) * 1000000;
    }

    void incre(int h);

    int calculateWeekDay() const {
        int m = mn, d = day, y = yr;
        if(m==1||m==2) //把一月和二月换算成上一年的十三月和是四月
        {
            m+=12;
            y--;
        }
        int weekDay = (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;//求出星期几
        return weekDay;
    }

    void pause();

    void recover();

    string toString();
};


// ????
class Clock {

public:
    int timestamp;
    Array<string>* info = new Array<string>(16);

    Clock(int timestamp);

    Clock();

    int getTimestamp() const;

    void setTimestamp(int timestamp);

    Array<string> *getInfo() const;

    void setInfo(Array<string> *info);

    bool addEvent(string event);
};

class OurStr
{
    public:
    /**
     * @brief 字符串比较函数
     * 
     * @param s1 
     * @param s2 
     * @return int -1时s1<s2,0时字符串相等,1时s1>s2
     */
        static int StrCmp(string s1, string s2)
        {
            int len = min(s1.length(), s2.length()), i;
            for(i = 0; i < len && s1[i] == s2[i]; i++);
            if(i == len)
            {
                if(s1.length() < s2.length()) return -1;
                else if(s1.length() > s2.length()) return 1;
                return 0;
            }
            if(i == s1.length() || s1[i] < s2[i]) return -1;
            return 1;
        }

        static string getFilename(string path)
        {
            int i;
            for(i = path.length() - 1; i >= 0; i--)
            {
                if(path[i] == '/' || path[i] == '\\') break;
            }
            return path.substr(i + 1);
        }

        static string getSuffix(string path)
        {
            int i;
            for(i = path.length() - 1; i >= 0; i--)
            {
                if(path[i] == '.') break;
            }
            return path.substr(i + 1);
        }
};

class Files
{
    public:   
        static void getFiles(string path, vector<string>& files)
        {
            //文件句柄  
            long   hFile = 0;
            //文件信息，声明一个存储文件信息的结构体  
            struct _finddata_t fileinfo;
            string p;//字符串，存放路径
            if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)//若查找成功，则进入
            {
                do
                {
                    //如果是目录,迭代之（即文件夹内还有文件夹）  
                    if ((fileinfo.attrib &  _A_SUBDIR))
                    {
                        //文件名不等于"."&&文件名不等于".."
                        //.表示当前目录
                        //..表示当前目录的父目录
                        //判断时，两者都要忽略，不然就无限递归跳不出去了！
                        if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                            getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
                    }
                    //如果不是,加入列表  
                    else
                    {
                        files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                    }
                } while (_findnext(hFile, &fileinfo) == 0);
                //_findclose函数结束查找
                _findclose(hFile);
            }
        }
};

#endif
