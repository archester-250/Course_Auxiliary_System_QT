#ifndef INPUT_H
#define INPUT_H
#include <conio.h>
#include <stdio.h>
#include <string>
using namespace std;

extern Time modtime;

template <typename T> T Input() {
    //TODO�������ʽ�����׳��쳣
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
            if(!flag) cout << "����Ĳ�������,����������!" << endl;
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
