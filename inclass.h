#ifndef INCLASS_H
#define INCLASS_H

#include <QDialog>
#include <QMessageBox>
#include "todaycourseinfo.h"
#include "searchcourse.h"
#include "seehomework.h"
#include "uploadhomework.h"
#include "openfile.h"
#include "src/student.h"

namespace Ui {
class Inclass;
}

class Inclass : public QDialog
{
    Q_OBJECT

public:
    explicit Inclass(QWidget *parent = nullptr);
    ~Inclass();

signals:
    void sendName(QString name);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void receiveName(QString name);

private:
    Ui::Inclass *ui;
    QString name;
};

#endif // INCLASS_H
