#include "seecoursedoc.h"
#include "ui_seecoursedoc.h"

SeeCourseDoc::SeeCourseDoc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeeCourseDoc)
{
    ui->setupUi(this);
}

SeeCourseDoc::~SeeCourseDoc()
{
    delete ui;
}
