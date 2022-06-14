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

signals:
    void sendName(QString name);

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void receiveName(QString s);

    void on_pushButton_clicked();

private:
    Ui::SystemChoose *ui;
    QString name;
};

#endif // SYSTEMCHOOSE_H
