#include "addcoursedoc.h"
#include "ui_addcoursedoc.h"

AddCourseDoc::AddCourseDoc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCourseDoc)
{
    ui->setupUi(this);
}

AddCourseDoc::~AddCourseDoc()
{
    delete ui;
}

void AddCourseDoc::on_pushButton_3_clicked()
{
    filename = QFileDialog::getOpenFileName(NULL, QStringLiteral("上传课程资料"));
}

