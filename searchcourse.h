#ifndef SEARCHCOURSE_H
#define SEARCHCOURSE_H

#include <QDialog>

namespace Ui {
class SearchCourse;
}

class SearchCourse : public QDialog
{
    Q_OBJECT

public:
    explicit SearchCourse(QWidget *parent = nullptr);
    ~SearchCourse();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::SearchCourse *ui;
};

#endif // SEARCHCOURSE_H
