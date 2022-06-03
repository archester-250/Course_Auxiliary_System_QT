#ifndef INPUT_H
#define INPUT_H
#include "src/utils.h"
#include <conio.h>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <string>
using namespace std;

extern Time modtime;

template <typename T> T Input() {
    //TODO：输入格式错误抛出异常
    modtime.pause();
    T in;
    cin >> in;
    modtime.recover();
    return in;
}

class input
{
private:
    /* data */
public:
    static int getOperatorNum()
    {
        char op;
        bool flag = true;
        do
        {
            if(!flag) cout << "输入的不是数字,请重新输入!" << endl;
            flag = false;
            while(!_kbhit());
            op = getch();
            printf("%d\n", op - '0');
            return op - '0';
            /* code */
        } while (!isdigit(op));
    }

};


#endif
