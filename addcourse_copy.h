#ifndef ADDCOURSE_COPY_H
#define ADDCOURSE_COPY_H

#include <QDialog>
#include <QMessageBox>
#include "src/admin.h"

namespace Ui {
class AddCourse;
}

class AddCourse : public QDialog
{
    Q_OBJECT

public:
    explicit AddCourse(QWidget *parent = nullptr);
    ~AddCourse();

private slots:
    void receiveName(QString name);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::AddCourse *ui;
    QString name;
    int i, timeSize;
    course_time * ct;
    string cname;
    string address;
    string current;
    string QQGroup;
    Time extime;
    string exaddress;
    string * students;
};

#endif // ADDCOURSE_COPY_H
