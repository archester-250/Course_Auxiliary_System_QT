#ifndef ADDCOURSEDOC_H
#define ADDCOURSEDOC_H

#include <QDialog>
#include <QFileDialog>

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

private:
    Ui::AddCourseDoc *ui;
    QString filename;
};

#endif // ADDCOURSEDOC_H
