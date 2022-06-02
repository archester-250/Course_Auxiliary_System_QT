#ifndef SYSTEMCHOOSE_H
#define SYSTEMCHOOSE_H

#include <QDialog>
#include "inclass.h"
#include "outofclass.h"

namespace Ui {
class SystemChoose;
}

class SystemChoose : public QDialog
{
    Q_OBJECT

public:
    explicit SystemChoose(QWidget *parent = nullptr);
    ~SystemChoose();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SystemChoose *ui;
};

#endif // SYSTEMCHOOSE_H
