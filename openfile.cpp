#include "openfile.h"
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
    for(int i = 0; i < c.getDocumentsSize(); i++)
    {
        text = QString::fromStdString(c.getDocuments()[i]);
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
    for(int i = 0; i < c.getHomeWorkSize(); i++)
    {
        text = QString::fromStdString(c.getHomeWork()[i] + "\n");
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
    else
    {

    }
}

