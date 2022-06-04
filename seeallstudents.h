#ifndef SEEALLSTUDENTS_H
#define SEEALLSTUDENTS_H

#include <QDialog>

namespace Ui {
class SeeAllStudents;
}

class SeeAllStudents : public QDialog
{
    Q_OBJECT

public:
    explicit SeeAllStudents(QWidget *parent = nullptr);
    ~SeeAllStudents();

private slots:
    void receiveName(QString name);

private:
    Ui::SeeAllStudents *ui;
    QString name;
};

#endif // SEEALLSTUDENTS_H
