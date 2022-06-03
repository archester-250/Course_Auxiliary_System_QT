#include "adminlogin.h"
#include "ui_adminlogin.h"

AdminLogin::AdminLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
}

AdminLogin::~AdminLogin()
{
    delete ui;
}

void AdminLogin::on_buttonBox_accepted()
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
    }
    if(flag)
    {
        QMessageBox::information(NULL, "Success", "登录成功!");
        AdminMenu am;
        am.exec();
    }
}

