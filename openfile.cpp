﻿#include "openfile.h"
#include "ui_openfile.h"

OpenFile::OpenFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFile)
{
    ui->setupUi(this);
    ui->radioButton->setCheckable(false);
    ui->radioButton_2->setCheckable(false);
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);
    ui->comboBox->setEditable(false);
    ui->comboBox->setEnabled(false);
}

OpenFile::~OpenFile()
{
    delete ui;
}

void OpenFile::on_radioButton_clicked()
{
    ui->radioButton->setChecked(true);
    ui->radioButton_2->setChecked(false);
    ui->comboBox->setEnabled(true);
    ui->comboBox->clear();
    QString text;
    for(int i = 0; i < c.getFinishSize(); i++)
    {
        text = QString::fromStdString(c.getFinish()[i].road);
        ui->comboBox->addItem(text);
    }
}


void OpenFile::on_radioButton_2_clicked()
{
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(true);
    ui->comboBox->setEnabled(true);
    ui->comboBox->clear();
    QString text;
    for(int i = 0; i < c.getDocumentsSize(); i++)
    {
        text = QString::fromStdString(c.getDocuments()[i]);
        ui->comboBox->addItem(text);
    }
}

void OpenFile::receiveName(QString name)
{
    this->name = name;
}


void OpenFile::on_lineEdit_editingFinished()
{
    QString courseName = ui->lineEdit->text();
    Student s(name.toStdString());
    c = s.searchCourse(s.getCourses(), s.getCourseSize(), courseName.toStdString());
    if(c.getName() != "null")
    {
        ui->radioButton->setCheckable(true);
        ui->radioButton_2->setCheckable(true);
    }
    else
    {
        QMessageBox::information(NULL, "提醒", "未找到课程!");
    }
}


void OpenFile::on_pushButton_2_clicked()
{
    int index = ui->comboBox->currentIndex();
    if(ui->radioButton->isChecked())
    {
        qDebug() << "[LOG] student " << name << " tries to open " << QString::fromStdString(c.getFinish()[index].road) << QString::fromStdString(modtime.toString());
        if(OurStr::getSuffix(c.getFinish()[index].road) != "txt" && OurStr::getSuffix(c.getFinish()[index].road) != "TXT")
        {
            if(QMessageBox::information(NULL, "提醒", "非压缩模式，点击确定打开文件！") == QMessageBox::Ok)
            {
                system(("..\\documents\\users\\" + name.toStdString() + "\\" + c.getName() + "\\" + to_string(index + 1) + '\\' + c.getFinish()[index].road).c_str());
            }
        }
        else
        {
            string inroad = "..\\documents\\users\\" + name.toStdString() + "\\" + c.getName() + "\\" + to_string(index + 1) + '\\' + c.getFinish()[index].road.substr(0, c.getFinish()[index].road.rfind('.'));
            string outroad = "..\\documents\\users\\" + name.toStdString() + "\\" + c.getName() + "\\" + to_string(index + 1) + '\\' + c.getFinish()[index].road;
            compression co;
            if(co.Decode(inroad, outroad))
            {
                if(QMessageBox::information(NULL, "提醒", "解压成功，点击确定打开文件！") == QMessageBox::Ok)
                {
                    system(("..\\documents\\users\\" + name.toStdString() + "\\" + c.getName() + "\\" + to_string(index + 1) + '\\' + c.getFinish()[index].road).c_str());
                    QMessageBox::information(NULL, "提醒", "浏览结束,自动删除解压文件");
                    system(("del ..\\documents\\users\\" + name.toStdString() + "\\" + c.getName() + "\\" + to_string(index + 1) + '\\' + c.getFinish()[index].road).c_str());
                }
            }
            else
            {
                QMessageBox::information(NULL, "Error", "解压失败！请联系开发者");
            }
        }

    }
    else
    {
        qDebug() << "[LOG] student " << name << " tries to open " << QString::fromStdString(c.getDocuments()[index]) << QString::fromStdString(modtime.toString());
        if(OurStr::getSuffix(c.getDocuments()[index]) != "txt" && OurStr::getSuffix(c.getDocuments()[index]) != "TXT")
        {
            if(QMessageBox::information(NULL, "提醒", "非压缩模式，点击确定打开文件！") == QMessageBox::Ok)
            {
                system(("..\\documents\\public\\" + c.getName()  + "\\" + c.getDocuments()[index]).c_str());
            }
        }
        else
        {
            string inroad = "..\\documents\\public\\" + c.getName() + "\\" + c.getDocuments()[index].substr(0, c.getDocuments()[index].rfind('.'));
            string outroad = "..\\documents\\public\\" + c.getName()  + "\\" + c.getDocuments()[index];
            compression co;
            if(co.Decode(inroad, outroad))
            {
                if(QMessageBox::information(NULL, "提醒", "解压成功，点击确定打开文件！") == QMessageBox::Ok)
                {
                    system(("..\\documents\\public\\" + c.getName()  + "\\" + c.getDocuments()[index]).c_str());
                    QMessageBox::information(NULL, "提醒", "浏览结束,自动删除解压文件");
                    system(("del ..\\documents\\public\\" + c.getName()  + "\\" + c.getDocuments()[index]).c_str());
                }
            }
            else
            {
                QMessageBox::information(NULL, "Error", "解压失败！请联系开发者");
            }
        }
    }
}

