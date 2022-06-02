#include "openfile.h"
#include "ui_openfile.h"

OpenFile::OpenFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFile)
{
    ui->setupUi(this);
}

OpenFile::~OpenFile()
{
    delete ui;
}

void OpenFile::on_radioButton_clicked()
{
    ui->radioButton->setChecked(true);
    ui->radioButton_2->setChecked(false);
}


void OpenFile::on_radioButton_2_clicked()
{
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(true);
}


