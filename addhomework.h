#ifndef ADDHOMEWORK_H
#define ADDHOMEWORK_H

#include <QDialog>

namespace Ui {
class AddHomework;
}

class AddHomework : public QDialog
{
    Q_OBJECT

public:
    explicit AddHomework(QWidget *parent = nullptr);
    ~AddHomework();

private:
    Ui::AddHomework *ui;
};

#endif // ADDHOMEWORK_H
