#include "seeallActivities.h"
#include "ui_seeallActivities.h"
#include "src/admin.h"
#include "utils.h"
#include "hashMap.h"
#include "activity.h"
#include "student.h"
#include "course.h"
#include "login.h"
#include "input.h"

SeeAllActivities::SeeAllActivities(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeeAllActivities)
{
    ui->setupUi(this);
    QString text;
    int sz = student->getActivityArray()->size;
        for (int i = 0; i < sz; i++) {
            Activity activity = student->getActivityArray()->get(i);
            text += text.number(i) + "." + text.fromStdString(activity.toString()) + "\n";
        }

        ui->textBrowser->insertPlainText(text);
}

SeeAllActivities::~SeeAllActivities()
{
    delete ui;
}

void SeeAllActivities::receiveName(QString name)
{
    this->name = name;
}
