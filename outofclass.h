#ifndef OUTOFCLASS_H
#define OUTOFCLASS_H

#include <QDialog>
#include "addActivity.h"
#include "addClock.h"
#include "seeallActivities.h"
#include "seeTodayActivities.h"
#include "src/student.h"

namespace Ui {
class OutOfClass;
}

class OutOfClass : public QDialog
{
    Q_OBJECT

public:
    explicit OutOfClass(QWidget *parent = nullptr);
    ~OutOfClass();

private slots:
    void receiveName(QString name);
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();


private:
    Ui::OutOfClass *ui;
    QString name;
};

#endif // OUTOFCLASS_H
