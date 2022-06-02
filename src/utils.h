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
//ʱ�䱶�ʣ�������3��һСʱ

using namespace std;

extern int sys_time_bias_times;

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

    Time desc(int h) {//????h��?
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
        if(m==1||m==2) //��һ�ºͶ��»������һ���ʮ���º�������
        {
            m+=12;
            y--;
        }
        int weekDay = (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;//������ڼ�
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
     * @brief �ַ����ȽϺ���
     * 
     * @param s1 
     * @param s2 
     * @return int -1ʱs1<s2,0ʱ�ַ������,1ʱs1>s2
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
            //�ļ����  
            long   hFile = 0;
            //�ļ���Ϣ������һ���洢�ļ���Ϣ�Ľṹ��  
            struct _finddata_t fileinfo;
            string p;//�ַ��������·��
            if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)//�����ҳɹ��������
            {
                do
                {
                    //�����Ŀ¼,����֮�����ļ����ڻ����ļ��У�  
                    if ((fileinfo.attrib &  _A_SUBDIR))
                    {
                        //�ļ���������"."&&�ļ���������".."
                        //.��ʾ��ǰĿ¼
                        //..��ʾ��ǰĿ¼�ĸ�Ŀ¼
                        //�ж�ʱ�����߶�Ҫ���ԣ���Ȼ�����޵ݹ�������ȥ�ˣ�
                        if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                            getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
                    }
                    //�������,�����б�  
                    else
                    {
                        files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                    }
                } while (_findnext(hFile, &fileinfo) == 0);
                //_findclose������������
                _findclose(hFile);
            }
        }
};

#endif
