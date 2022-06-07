#include "seeallActivities.h"
#include "ui_seeallActivities.h"
#include "src/admin.h"
#include "src/utils.h"
#include "src/hashMap.h"
#include "src/activity.h"
#include "src/student.h"
#include "src/course.h"
#include "src/login.h"
#include "src/input.h"

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
