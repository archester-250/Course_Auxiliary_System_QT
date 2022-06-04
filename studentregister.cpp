#include "studentregister.h"
#include "ui_studentregister.h"
#include "src/login.h"

StudentRegister::StudentRegister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentRegister)
{
    ui->setupUi(this);
}

StudentRegister::~StudentRegister()
{
    delete ui;
}

void StudentRegister::on_buttonBox_accepted()
{
    bool flag = true;
    name = ui->lineEdit->text();
    if(name.isEmpty())
    {
        QMessageBox::information(NULL, "Error", "输入姓名为空!");
        flag = false;
    }
    else
    {
        password = ui->lineEdit_2->text();
        if(password.isEmpty())
        {
            QMessageBox::information(NULL, "Error", "输入密码为空!");
            flag = false;
        }
        else if(login::match(name.toStdString(), password.toStdString(), 3))
        {
            QMessageBox::information(NULL, "Error", "账户已经注册！");
            flag = false;
        }
    }
    if(flag)
    {
        QMessageBox::information(NULL, "Success", "注册成功!");
        login::writeIn(name.toStdString(), password.toStdString(), 3);
    }
}

