#ifndef SEETODAYACTIVITIES_H
#define SEETODAYACTIVITIES_H

#include <QDialog>

namespace Ui {
class SeeTodayActivities;
}

class SeeTodayActivities : public QDialog
{
    Q_OBJECT

public:
    explicit SeeTodayActivities(QWidget *parent = nullptr);
    ~SeeTodayActivities();

private:
    Ui::SeeTodayActivities *ui;
    QString name;
};

#endif // SEETODAYACTIVITIES_H
