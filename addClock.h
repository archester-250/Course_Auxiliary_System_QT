#ifndef ADDCLK_H
#define ADDCLK_H

#include <QDialog>
#include <QMessageBox>
#include "src/admin.h"

namespace Ui {
class AddClock;
}

class AddClock : public QDialog
{
    Q_OBJECT

public:
    explicit AddClock(QWidget *parent = nullptr);
    ~ AddClock();

private slots:
    void receiveName(QString name);
    void on_pushButton_2_clicked();

private:
    Ui::AddClock *ui;
    QString name;

};

#endif // ADDCLK_H
