#include "seeTodayActivities.h"
#include "ui_seeTodayActivities.h"
#include "src/student.h"
#include "utils.h"
#include "hashMap.h"
#include "activity.h"
#include "student.h"
#include "course.h"
#include "login.h"
#include "input.h"

SeeTodayActivities::SeeTodayActivities(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeeTodayActivities)
{
    ui->setupUi(this);
    QString text;
    int sz = student->getActivityArray()->size;
        for (int i = 0; i < sz; i++) {
            Activity activity = student->getActivityArray()->get(i);
            if (activity.getStartTime().day != modtime.day) {
                        continue;
                   }
            text += text.number(i) + "." + text.fromStdString(activity.toString()) + "\n";
        }

        ui->textBrowser->insertPlainText(text);
}

SeeTodayActivities::~SeeTodayActivities()
{
    delete ui;
}
