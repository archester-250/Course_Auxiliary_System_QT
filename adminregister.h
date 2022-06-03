#ifndef ADMINREGISTER_H
#define ADMINREGISTER_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AdminRegister;
}

class AdminRegister : public QDialog
{
    Q_OBJECT

public:
    explicit AdminRegister(QWidget *parent = nullptr);
    ~AdminRegister();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AdminRegister *ui;
    QString name;
    QString password;
};

#endif // ADMINREGISTER_H
