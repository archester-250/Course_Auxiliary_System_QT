#ifndef SEEHOMEWORK_H
#define SEEHOMEWORK_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class SeeHomework;
}

class SeeHomework : public QDialog
{
    Q_OBJECT

public:
    explicit SeeHomework(QWidget *parent = nullptr);
    ~SeeHomework();

private slots:
    void receiveName(QString name);

    void on_pushButton_2_clicked();

private:
    Ui::SeeHomework *ui;
    QString name;
};

#endif // SEEHOMEWORK_H
