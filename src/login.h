/**
 * @file login.h
 * @author wxl (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "hashMap.h"
#include "utils.h"
#include "input.h"
#include "student.h"
#include "admin.h"

using namespace std;
extern Student* student;
extern Admin* admin;

struct info
{
    int notEnd;
    string user;
    /* data */
};

extern Time modtime;


class login
{
private:
    /* data */
public:
    static info dologin()
    {
        printf("��ӭʹ�ÿγ̸���ϵͳ��(����0�˳���\n");
        printf("��ѡ���¼��ʽ\n1��ѧ���û�\t2������Ա\t3��ע��ѧ��\t4��ע�����Ա\n(����Ҫ��enter��!^_^)");
        info inf;
        input in;
        int loginCode;
        loginCode = in.getOperatorNum();
        if (loginCode == 0)
        {
            inf.notEnd = 0;
            return inf;
        }
        if ((loginCode == 1 || loginCode == 2)) {
            string username;
            do
            {
                printf("�������û���(���ܳ���20λ������һ����ռ2λ):");
                username = Input<string>();
            } while (username.length() > 20);
            string password;
            do
            {
                printf("����������(���ܳ���20λ������һ����ռ2λ):");
                password = Input<string>();
            }while(password.length() > 20);
            if (match(username, password, loginCode))
            {
                printf("��½�ɹ���\n");
                inf.notEnd = loginCode;
                inf.user = username;
                return inf;
            }
            else printf("��½ʧ�ܣ�\n");
        }
        else if (loginCode == 3 || loginCode == 4) {
            string username;
            do
            {
                printf("�������û���(���ܳ���20λ������һ����ռ2λ):");
                username = Input<string>();
            } while (username.length() > 20);
            string password;
            do
            {
                printf("����������(���ܳ���20λ������һ����ռ2λ):");
                password = Input<string>();
            }while(password.length() > 20);
            writeIn(username, password, loginCode);
            if(loginCode == 3)
            {
                string cmd = "mkdir ..\\documents\\users\\" + username;
                system(cmd.c_str());
                cmd = "cd ..\\documents\\users\\" + username + " & echo 0 > " + username + ".data";
                system(cmd.c_str());
                cmd = "cd ..\\documents\\users\\" + username + " & type nul > courseTable_" + username + ".csv";
                system(cmd.c_str());
                ifstream fin("../database/Administer.data");
                int n;
                fin >> n;
                string names[n];
                for(int i = 0; i < n; i++)
                {
                    fin >> names[i];
                }
                fin.close();
                ofstream fout("../database/Administer.data");
                fout << n + 1 << endl;
                fout << username;
                for(int i = 0; i < n; i++)
                {
                    fout << ' ' << names[i];
                }
                fout.close();
            }
        } else
            return inf;
        inf.notEnd = 5;
        return inf;
    }
    static void writeIn(string user, string password, int loginCode)
    {
        try
        {
            if(match(user, password, loginCode) && loginCode == 3) throw 2;
            FILE * fp;
            if(loginCode == 3) fp = fopen("../database/users.data", "a");
            else fp = fopen("../database/administers.data", "a");
            if(fp == NULL) throw 0;
            if(fprintf(fp, "%s %s\n", user.c_str(), password.c_str()) < 0)
            {
                fclose(fp);
                throw 1;
            }
            fclose(fp);
        }
        catch(int error)
        {
            switch (error)
            {
            case 0:
                printf("Not found the file!\n");
                break;

            case 1:
                printf("Write in error!\n");
                break;

            case 2:
                printf("Repetive user's name!\n");

            default:
                break;
            }
        }
    }
    static bool match(string s1, string s2, int loginCode)
    {
        try
        {

            string s0;
            if(loginCode == 1 || loginCode == 3) s0 = "../database/users.data";
            else s0 = "../database/administers.data";
            ifstream in(s0);
            char c;
            int index = 0;
            string temp, temp1;
            if(loginCode == 1 || loginCode == 2)
            {
                s1 = s1 + ' ' + s2;
                while (in >> temp >> temp1)
                {
                    if(!OurStr::StrCmp(s1, temp + ' ' + temp1))
                    {
                        in.close();
                        return true;
                    }
                }
            }
            else
            {
                while (in >> temp)
                {
                    if(!OurStr::StrCmp(s1, temp))
                    {
                        in.close();
                        return true;
                    }
                    in >> temp;
                }

            }
            in.close();
            return false;
        }
        catch(int error)
        {
            switch (error)
            {
            case 0:
                printf("Not found the file!\n");
                break;

            default:
                break;
            }
        }
        return false;
    }
    static bool inputString(char * str)
    {
        char c;
        int index = 0;
        try
        {
            while((c = getchar()) != '\n')
            {
                if(index == 20) throw 0;
                str[index++] = c;
            }
        }
        catch(int error)
        {
            switch (error)
            {
            case 0:
                printf("The input exceeds the maximum limit!\n");
                while(getchar() != '\n');
                return false;
                break;

            default:
                break;
            }
        }
        return true;
    }
};

#endif
