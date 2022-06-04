#ifndef SEEALLCOURSES_H
#define SEEALLCOURSES_H

#include <QDialog>

namespace Ui {
class SeeAllCourses;
}

class SeeAllCourses : public QDialog
{
    Q_OBJECT

public:
    explicit SeeAllCourses(QWidget *parent = nullptr);
    ~SeeAllCourses();

private slots:
    void receiveName(QString name);

private:
    Ui::SeeAllCourses *ui;
    QString name;
};

#endif // SEEALLCOURSES_H
