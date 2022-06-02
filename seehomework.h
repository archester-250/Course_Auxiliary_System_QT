#ifndef SEEHOMEWORK_H
#define SEEHOMEWORK_H

#include <QDialog>

namespace Ui {
class SeeHomework;
}

class SeeHomework : public QDialog
{
    Q_OBJECT

public:
    explicit SeeHomework(QWidget *parent = nullptr);
    ~SeeHomework();

private:
    Ui::SeeHomework *ui;
};

#endif // SEEHOMEWORK_H
