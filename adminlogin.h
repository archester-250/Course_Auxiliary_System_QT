#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QDialog>
#include <QMessageBox>
#include "adminmenu.h"

namespace Ui {
class AdminLogin;
}

class AdminLogin : public QDialog
{
    Q_OBJECT

public:
    explicit AdminLogin(QWidget *parent = nullptr);
    ~AdminLogin();

signals:
    void sendName(QString name);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AdminLogin *ui;
    QString name;
    QString password;
};

#endif // ADMINLOGIN_H
