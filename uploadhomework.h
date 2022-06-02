#ifndef UPLOADHOMEWORK_H
#define UPLOADHOMEWORK_H

#include <QDialog>
#include <QFileDialog>

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

private:
    Ui::UploadHomework *ui;
    QString filename;
};

#endif // UPLOADHOMEWORK_H
