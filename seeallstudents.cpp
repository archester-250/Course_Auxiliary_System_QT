#include "seeallstudents.h"
#include "ui_seeallstudents.h"
#include "src/admin.h"

SeeAllStudents::SeeAllStudents(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeeAllStudents)
{
    ui->setupUi(this);
    Admin a(name.toStdString());
    for(int i = 0; i < a.getStudent_size(); i++)
    {
        QString text;
        text += QString::fromStdString("学生" + to_string(i + 1) + ":" + a.getStudents()[i].getName() + "\n");
        ui->textBrowser->insertPlainText(text);
    }
}

SeeAllStudents::~SeeAllStudents()
{
    delete ui;
}

void SeeAllStudents::receiveName(QString name)
{
    this->name = name;
}
