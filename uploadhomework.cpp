#include "uploadhomework.h"
#include "ui_uploadhomework.h"

UploadHomework::UploadHomework(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UploadHomework)
{
    ui->setupUi(this);
}

UploadHomework::~UploadHomework()
{
    delete ui;
}

void UploadHomework::on_pushButton_2_clicked()
{
    filename = QFileDialog::getOpenFileName(NULL, QStringLiteral("上传作业文件"));
}

