#include "studentlogin.h"
#include "ui_studentlogin.h"

StudentLogin::StudentLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentLogin)
{
    ui->setupUi(this);
}

StudentLogin::~StudentLogin()
{
    delete ui;
}



void StudentLogin::on_buttonBox_accepted()
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
        else if(!login::match(name.toStdString(), password.toStdString(), 1))
        {
            QMessageBox::information(NULL, "Error", "用户尚未注册或与密码不匹配!");
            flag = false;
        }
    }
    if(flag)
    {
        QMessageBox::information(NULL, "Success", "登录成功!");
        SystemChoose sc;
        connect(this, SIGNAL(sendName(QString)), &sc, SLOT(receiveName(QString)));
        emit sendName(name);
        sc.exec();
    }
}
