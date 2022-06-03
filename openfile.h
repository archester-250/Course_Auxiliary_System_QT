#ifndef OPENFILE_H
#define OPENFILE_H

#include <QDialog>
#include "src/student.h"

namespace Ui {
class OpenFile;
}

class OpenFile : public QDialog
{
    Q_OBJECT

public:
    explicit OpenFile(QWidget *parent = nullptr);
    ~OpenFile();

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void receiveName(QString name);

    void on_lineEdit_editingFinished();

    void on_pushButton_2_clicked();

private:
    Ui::OpenFile *ui;
    QString name;
    course c;
};

#endif // OPENFILE_H
