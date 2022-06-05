#ifndef ADDACTIVITY_H
#define ADDACTIVITY_H

#include <QDialog>
#include <QMessageBox>
#include "src/admin.h"

namespace Ui {
class AddActivity;
}

class AddActivity : public QDialog
{
    Q_OBJECT

public:
    explicit  AddActivity(QWidget *parent = nullptr);
    ~ AddActivity();

private slots:
    void receiveName(QString name);
    void on_pushButton_2_clicked();
    void on_pushButton_add_clicked();
private:
    Ui::AddActivity *ui;
    QString name;
    Time startTime;
    Time endTime;//活动起止时间
    string address;
    int clk;
    int memberCnt;
    Array<string>* members;
    string description;//活动内容描述
    string storeStr = "NULL";
};

#endif // ADDACTIVITY_H
