#include "addcourse.h"
#include "ui_addcourse.h"

AddCourse::AddCourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCourse)
{
    ui->setupUi(this);
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->formLayoutWidget_2->hide();
    ui->formLayoutWidget_3->hide();
}

AddCourse::~AddCourse()
{
    delete ui;
}

void AddCourse::receiveName(QString name)
{
    this->name = name;
}

void AddCourse::on_pushButton_2_clicked()
{
    Admin a(name.toStdString());
    cname = ui->lineEdit->text().toStdString();
    timeSize = ui->lineEdit_2->text().toInt();
    ct = (course_time *)malloc(timeSize * sizeof(course_time));
    address = ui->lineEdit_3->text().toStdString();
    current = ui->lineEdit_4->text().toStdString();
    QQGroup = ui->lineEdit_5->text().toStdString();
    QDate date = ui->dateTimeEdit->date();
    QTime time = ui->dateTimeEdit->time();
    extime.yr = date.year();
    extime.mn = date.month();
    extime.day = date.day();
    extime.hr = time.hour();
    exaddress = ui->lineEdit_6->text().toStdString();
    if(cname.empty() || address.empty() || current.empty() || QQGroup.empty() || exaddress.empty())
    {
        QMessageBox::information(NULL, "Error", "请把信息填写完整！");
        return;
    }
    ui->formLayoutWidget->hide();
    ui->formLayoutWidget_2->show();
    ui->pushButton_2->hide();
    ui->pushButton_3->show();
    i = 0;
    ui->label_9->setText(QString::fromStdString("请输入第" + to_string(i + 1) + "次课程开始时间："));
    ui->label_10->setText(QString::fromStdString("请输入第" + to_string(i + 1) + "次课程结束时间："));
    ui->label_11->setText(QString::fromStdString("请输入第" + to_string(i + 1) + "次课程在周几上课(0-6)："));
}


void AddCourse::on_pushButton_3_clicked()
{
    Admin a(name.toStdString());
    if(i == timeSize - 1)
    {
        ct[i].starthour = ui->lineEdit_7->text().toInt();
        ct[i].endhour = ui->lineEdit_8->text().toInt();
        ct[i].week = ui->lineEdit_9->text().toInt();
        for(int j = 0; j < a.getCourse_size(); j++)
        {
            for(int k = 0; k < a.getCourses()[j].getTimeSize(); k++)
            {
                if(ct[i].week == a.getCourses()[j].getTime()[k].week &&
                ((ct[i].starthour >= a.getCourses()[j].getTime()[k].starthour && ct[i].starthour < a.getCourses()[j].getTime()[k].endhour) ||
                (ct[i].endhour > a.getCourses()[j].getTime()[k].starthour && ct[i].endhour <= a.getCourses()[j].getTime()[k].endhour)))
                {
                    QMessageBox::information(NULL, "Error", "课程冲突，请重新输入");
                    return;
                }
            }
        }
        a.addCourse(cname, timeSize, ct, address, current, QQGroup, extime, exaddress);
        a.saveCourseInfo();
        free(ct);
        ui->formLayoutWidget_2->hide();
        ui->pushButton_3->hide();
        ui->formLayoutWidget_3->show();
        ui->pushButton_4->show();
        ui->pushButton_5->show();
        students = new string[a.getStudent_size()];
    }
    else
    {
        ct[i].starthour = ui->lineEdit_7->text().toInt();
        ct[i].endhour = ui->lineEdit_8->text().toInt();
        ct[i].week = ui->lineEdit_9->text().toInt();
        for(int j = 0; j < a.getCourse_size(); j++)
        {
            for(int k = 0; k < a.getCourses()[j].getTimeSize(); k++)
            {
                if(ct[i].week == a.getCourses()[j].getTime()[k].week &&
                (ct[i].starthour >= a.getCourses()[j].getTime()[k].starthour && ct[i].starthour < a.getCourses()[j].getTime()[k].endhour) ||
                (ct[i].endhour > a.getCourses()[j].getTime()[k].starthour && ct[i].endhour <= a.getCourses()[j].getTime()[k].endhour))
                {
                    QMessageBox::information(NULL, "Error", "课程冲突，请重新输入");
                    return;
                }
            }
        }
        i++;
        ui->label_9->setText(QString::fromStdString("请输入第" + to_string(i + 1) + "次课程开始时间："));
        ui->label_10->setText(QString::fromStdString("请输入第" + to_string(i + 1) + "次课程结束时间："));
        ui->label_11->setText(QString::fromStdString("请输入第" + to_string(i + 1) + "次课程在周几上课(0-6)："));
    }
}


void AddCourse::on_pushButton_4_clicked()
{
    Admin a(name.toStdString());
    string stuname = ui->lineEdit_10->text().toStdString();
    if(stuname.empty())
    {
        QMessageBox::information(NULL, "Error", "输入学生为空！");
        return;
    }
    fstream in("../database/users.data");
    string sname, temp;
    bool flag = false;
    while(in >> sname >> temp)
    {
        if(!OurStr::StrCmp(stuname, sname))
        {
            flag = true;
            break;
        }
    }
    in.close();
    if(flag)
    {
        string cmd = "mkdir ..\\documents\\users\\" + stuname + "\\" + cname;
        system(cmd.c_str());
        for(int i = 0; i < a.getStudent_size(); i++)
        {
            if(!OurStr::StrCmp(a.getStudents()[i].getName(), stuname))
            {
                a.getStudents()[i].setCourseSize(a.getStudents()[i].getCourseSize() + 1);
                course * newCourse = new course[a.getStudents()[i].getCourseSize()];
                for(int j = 0; j < a.getStudents()[i].getCourseSize() - 1; j++)
                {
                    newCourse[j] = a.getStudents()[i].getCourses()[j];
                }
                newCourse[a.getStudents()[i].getCourseSize() - 1] = a.getCourses()[a.getCourse_size() - 1];
                a.getStudents()[i].setCourses(newCourse, a.getStudents()[i].getCourseSize());
                delete [] newCourse;
                a.getStudents()[i].saveStuInfo();
                break;
            }
        }
        QMessageBox::information(NULL, "添加成功", "已成功添加该学生！");
        qDebug() << "[LOG] administer" << name << "adds course " << QString::fromStdString(cname)
                 << " to student" << QString::fromStdString(stuname) << QString::fromStdString(modtime.toString());
    }
    else
    {
        QMessageBox::information(NULL, "Error", "未找到该学生！");
    }
}

