#ifndef SEEALLACTIVITIES_H
#define SEEALLACTIVITIES_H

#include <QDialog>

namespace Ui {
class SeeAllActivities;
}

class SeeAllActivities : public QDialog
{
    Q_OBJECT

public:
    explicit SeeAllActivities(QWidget *parent = nullptr);
    ~SeeAllActivities();

private slots:
    void receiveName(QString name);

private:
    Ui::SeeAllActivities *ui;
    QString name;
};

#endif // SEEALLACTIVITIES_H
