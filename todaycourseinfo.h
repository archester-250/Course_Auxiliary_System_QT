#ifndef TODAYCOURSEINFO_H
#define TODAYCOURSEINFO_H

#include <QDialog>

namespace Ui {
class TodayCourseInfo;
}

class TodayCourseInfo : public QDialog
{
    Q_OBJECT

public:
    explicit TodayCourseInfo(QWidget *parent = nullptr);
    ~TodayCourseInfo();

private:
    Ui::TodayCourseInfo *ui;
};

#endif // TODAYCOURSEINFO_H
