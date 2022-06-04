#ifndef ADDHOMEWORK_H
#define ADDHOMEWORK_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AddHomework;
}

class AddHomework : public QDialog
{
    Q_OBJECT

public:
    explicit AddHomework(QWidget *parent = nullptr);
    ~AddHomework();

private slots:
    void receiveName(QString name);

    void on_pushButton_2_clicked();

private:
    Ui::AddHomework *ui;
    QString name;
};

#endif // ADDHOMEWORK_H
