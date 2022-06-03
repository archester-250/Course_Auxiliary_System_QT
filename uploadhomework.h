#ifndef UPLOADHOMEWORK_H
#define UPLOADHOMEWORK_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "src/student.h"

namespace Ui {
class UploadHomework;
}

class UploadHomework : public QDialog
{
    Q_OBJECT

public:
    explicit UploadHomework(QWidget *parent = nullptr);
    ~UploadHomework();

private slots:
    void on_pushButton_2_clicked();

    void receiveName(QString name);

    void on_lineEdit_editingFinished();

    void on_pushButton_3_clicked();

private:
    Ui::UploadHomework *ui;
    QString filename;
    QString name;
    course c;
    string stuName;
};

#endif // UPLOADHOMEWORK_H
