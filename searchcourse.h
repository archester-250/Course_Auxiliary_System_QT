﻿#ifndef SEARCHCOURSE_H
#define SEARCHCOURSE_H

#include <QDialog>
#include <QMessageBox>
#include "src/student.h"

namespace Ui {
class SearchCourse;
}

class SearchCourse : public QDialog
{
    Q_OBJECT

public:
    explicit SearchCourse(QWidget *parent = nullptr);
    ~SearchCourse();

private slots:
    void on_pushButton_2_clicked();

    void receiveName(QString name);

private:
    Ui::SearchCourse *ui;
    QString name;
};

#endif // SEARCHCOURSE_H
