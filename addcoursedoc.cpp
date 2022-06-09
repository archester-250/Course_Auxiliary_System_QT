#include "addcoursedoc.h"
#include "ui_addcoursedoc.h"
#include "src/admin.h"

AddCourseDoc::AddCourseDoc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCourseDoc)
{
    ui->setupUi(this);
    ui->label_3->setText("当前无选择文件!");
}

AddCourseDoc::~AddCourseDoc()
{
    delete ui;
}

void AddCourseDoc::on_pushButton_3_clicked()
{
    filename = QFileDialog::getOpenFileName(NULL, QStringLiteral("上传课程资料"));
    for(int i = 0; i < filename.length(); i++)
    {
        if(filename[i] == '/')
        {
            filename[i] = '\\';
        }
    }
    ui->label_3->setText("当前文件:" + filename);
}

void AddCourseDoc::receiveName(QString name)
{
    this->name = name;
}

void AddCourseDoc::on_pushButton_2_clicked()
{
    string course_name = ui->lineEdit->text().toStdString();
    Admin a(name.toStdString());
    Student s;
    course c;
    c = s.searchCourse(a.getCourses(), a.getCourse_size(), course_name);
    if(c.getName() == "null")
    {
        QMessageBox::information(NULL, "Error", "没有找到该课程！");
        return;
    }
    for(int i = 0; i < c.getDocumentsSize(); i++)
    {
        if(!OurStr::StrCmp(c.getDocuments()[i], OurStr::getFilename(filename.toStdString())))
        {
            QMessageBox::information(NULL, "Error", "该资料已存在！");
            return;
        }
    }
    if(OurStr::getSuffix(filename.toStdString()) == "txt")
    {
        string outRoad = "..\\documents\\public\\" + course_name + "\\" + OurStr::getFilename(filename.toStdString()).substr(0, OurStr::getFilename(filename.toStdString()).length() - 4);
        compression com;
        if(com.Code(filename.toStdString(), outRoad))
        {
            QMessageBox::information(NULL, "提示", "压缩上传成功！");
        }
        else
        {
            QMessageBox::information(NULL, "提示", "压缩上传失败！请联系开发者");
        }
    }
    else
    {
        string cmd = "copy " + filename.toStdString() + " ..\\documents\\public\\" + course_name;
        system(cmd.c_str());
        QMessageBox::information(NULL, "提示", "非压缩上传成功！");
    }
    for(int i = 0; i < a.getCourse_size(); i++)
    {
        if(!OurStr::StrCmp(a.getCourses()[i].getName(), course_name))
        {
            string * newDocuments = new string[a.getCourses()[i].getDocumentsSize() + 1];
            for(int j = 0; j < a.getCourses()[i].getDocumentsSize(); j++)
            {
                newDocuments[j] = a.getCourses()[i].getDocuments()[j];
            }
            newDocuments[a.getCourses()[i].getDocumentsSize()] = OurStr::getFilename(filename.toStdString());
            a.getCourses()[i].setDocuments(newDocuments, a.getCourses()[i].getDocumentsSize() + 1);
            delete [] newDocuments;
        }
    }
    qDebug() << "[LOG] administer " << name << " upload file " << QString::fromStdString(OurStr::getFilename(filename.toStdString())) << QString::fromStdString(modtime.toString());
    a.saveAdminInfo();
}

