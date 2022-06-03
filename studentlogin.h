#ifndef STUDENTLOGIN_H
#define STUDENTLOGIN_H

#include <QDialog>
#include <QMessageBox>
#include "systemchoose.h"
#include "src/login.h"

namespace Ui {
class StudentLogin;
}

class StudentLogin : public QDialog
{
    Q_OBJECT

public:
    explicit StudentLogin(QWidget *parent = nullptr);
    ~StudentLogin();

signals:
    void sendName(QString s);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::StudentLogin *ui;
    QString name;
    QString password;
};

#endif // STUDENTLOGIN_H
