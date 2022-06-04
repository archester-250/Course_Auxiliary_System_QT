#include "uploadhomework.h"
#include "ui_uploadhomework.h"

UploadHomework::UploadHomework(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UploadHomework)
{
    ui->setupUi(this);
    QString text = QString::fromStdString("当前选择文件为空");
    ui->label_3->setText(text);
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(1);
}

UploadHomework::~UploadHomework()
{
    delete ui;
}

void UploadHomework::on_pushButton_2_clicked()
{
    filename = QFileDialog::getOpenFileName(NULL, QStringLiteral("上传作业文件"));
    QString text = QString::fromStdString("当前文件为:") + filename;
    ui->label_3->setText(text);
    ui->label_3->adjustSize();
}

void UploadHomework::receiveName(QString name)
{
    this->name = name;
}


void UploadHomework::on_lineEdit_editingFinished()
{
    QString courseName = ui->lineEdit->text();
    Student s(name.toStdString());
    c = s.searchCourse(s.getCourses(), s.getCourseSize(), courseName.toStdString());
    if(c.getName() != "null")
    {
        ui->spinBox->setMaximum(c.getHomeWorkSize());
        stuName = s.getName();
    }
    else
    {
        QMessageBox::information(NULL, "提醒", "未找到课程!");
    }
}


void UploadHomework::on_pushButton_3_clicked()
{
    int no = ui->spinBox->value();
    c.uploadHomework(filename.toStdString(), stuName, no - 1);
    Student s(stuName);
    for(int i = 0; i < s.getCourseSize(); i++)
    {
        if(s.getCourses()[i].getName() == c.getName())
        {
            s.getCourses()[i] = c;
            break;
        }
    }
    s.saveStuInfo();
}

