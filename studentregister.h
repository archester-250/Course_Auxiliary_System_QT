#ifndef STUDENTREGISTER_H
#define STUDENTREGISTER_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class StudentRegister;
}

class StudentRegister : public QDialog
{
    Q_OBJECT

public:
    explicit StudentRegister(QWidget *parent = nullptr);
    ~StudentRegister();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::StudentRegister *ui;
    QString name;
    QString password;
};

#endif // STUDENTREGISTER_H
