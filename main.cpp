#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ifstream config("../database/config");
    int init_time = 0;
    config >> init_time;
    modtime.inputTime(init_time);
    updateTime();
    config.close();
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Course_Auxiliary_System_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.setWindowTitle(QString::fromStdString("课程辅助系统"));  //修改这句即可，但是字母，汉字乱码
    w.show();
    int con = a.exec();
    ofstream _config("../database/config");
    _config << modtime.timeStamp();
    _config.close();
    return con;
}
