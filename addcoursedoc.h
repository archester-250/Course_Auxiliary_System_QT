#ifndef ADDCOURSEDOC_H
#define ADDCOURSEDOC_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class AddCourseDoc;
}

class AddCourseDoc : public QDialog
{
    Q_OBJECT

public:
    explicit AddCourseDoc(QWidget *parent = nullptr);
    ~AddCourseDoc();

private slots:
    void on_pushButton_3_clicked();

    void receiveName(QString name);

    void on_pushButton_2_clicked();

private:
    Ui::AddCourseDoc *ui;
    QString filename;
    QString name;
};

#endif // ADDCOURSEDOC_H
