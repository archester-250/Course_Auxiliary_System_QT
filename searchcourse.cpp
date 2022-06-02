#include "searchcourse.h"
#include "ui_searchcourse.h"

SearchCourse::SearchCourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchCourse)
{
    ui->setupUi(this);
}

SearchCourse::~SearchCourse()
{
    delete ui;
}

void SearchCourse::on_pushButton_2_clicked()
{

}

