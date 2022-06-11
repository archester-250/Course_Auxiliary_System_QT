#include "mainwindow.h"
#include <iostream>
#include <QApplication>

const char *ADJMAP_PATH = "../NAV/adjmap.txt";
const char *VERTICES_PATH = "../NAV/vertices.txt";
const char *L2P_PATH = "../NAV/l2p.txt";
const char *SHUTTLE_SCHEDULE_PATH = "../NAV/shuttle_schedule.txt";
const char *ACCOUNTS_PATH = "../NAV/accounts.txt";
//日志文件
const char *LOG_PATH = "../NAV/log.txt";

//日志文件各�?�操�?
const char *SWC_SHAHE = "切换沙河地图";
const char *SWC_BETWEEN = "切换校�?�地�?";
const char *SWC_BENBU = "切换�?部地�?";
const char *FINDPATH = "两点寻路";
const char *ANTFIND = "多点寻路";
const char *SEARCH = "搜索地点";
const char *SEARCH_NEAR = "搜索附近";
const char *SET_TIME = "设置时间";
const char *SET_V = "设置速度";
const char *DOUBLE_CLICK = "查看地点";
const char *FUZZY_SEARCH = "模糊搜索";
const char *REENTER = "重新输入";
const char *GOTO_CLASS = "前往教�??";

//bus的运营时�?
const int BUS_BEGIN_SEC = 21600;
const int BUS_END_SEC = 82920;
const int BUS_INTERVAL_SEC = 420;

//current的速度
const qreal STOP = 0;
const qreal FOOT = 1.2;
const qreal BIKE = 3.5;
const qreal SHUTTLE = 12.5;
const qreal BUS = 6.5;

const int GRID_ROWS = 20;

//沙河、本部中节点的最大序�?
const int SHAHE_MAX_NO = 131;
const int BETWEEN_MIN_NO = 132;
const int BETWEEN_MAX_NO = 141;
const int BENBU_MAX_NO = 360;

//两个校区的班车点、公交点的编�?
//bus点就�?校区的校门点
const int SHAHE_BUS_VER_NO = 0;
const int BENBU_BUS_VER_NO = 142;
const int SHAHE_SHUTTLE_VER_NO = 76;
const int BENBU_SHUTTLE_VER_NO = 157;

//�?间线�?的编号表示形�?
//�?间�?�按设定好的�?线走即可
const QVector<int> S2B_BUS_PATH_NO={0,132,133,134,135,136,141,142};
const QVector<int> S2B_SHUTTLE_PATH_NO = {76,74,56,45,44,42,41,39,4,2,1,0,132,137,138,139,140,141,142,143,155,156,157};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login login;
    if(login.exec()==QDialog::Accepted){
        MainWindow mw(login.get_online_account());
        mw.show();
        return a.exec();
    }
    return 0;
}
